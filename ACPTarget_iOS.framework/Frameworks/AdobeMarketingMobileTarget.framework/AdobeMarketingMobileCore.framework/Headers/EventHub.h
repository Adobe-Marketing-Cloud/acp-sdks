/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2017 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

#ifndef ADOBEMOBILE_CORE_EVENTHUB_H
#define ADOBEMOBILE_CORE_EVENTHUB_H

#include <deque>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <typeinfo>
#include "Object.h"
#include "Event.h"
#include "TaskExecutor.h"

namespace AdobeMarketingMobile {
    class Rule;
    class Module;
    class ModuleEventListenerBase;
    class ModuleEventProcessorBase;
    class PlatformServicesInterface;
    class TaskExecutor;
    class EventHubData;
    enum class EventHubState : int32_t;
    class ExternalModuleInterface;

    // declaration of global shared state variables
    extern const std::shared_ptr<EventData>
    SHARED_STATE_PENDING; ///< state that is "on the way" and will eventually be resolved.
    extern const std::shared_ptr<EventData>
    SHARED_STATE_PREV; ///< special "marker" state that indicates that this state is equal to the previous state.
    extern const std::shared_ptr<EventData>
    SHARED_STATE_NEXT; ///< special "marker" state that indicates that this state is equal to the next DATA/PENDING/INVALID state.
    extern const std::shared_ptr<EventData>
    SHARED_STATE_INVALID; ///< special state that indicates that the state is not valid.

    /**
     * @class EventHub
     *
     * Core event loop for SDK activity. The EventHub manages module lifetime, dispatches events, dispatches
     * callbacks, and manages the necessary threading.
     *
     * Starting an EventHub
     * ====================
     * EventHub::Create() can be used to create and start the event hub.
     * After calling RegisterModule for all modules, EventHub::FinishModuleRegistration()
     * should be called to complete the startup process. This method will dispatch a HUB BOOTED event.
     *
     * Stopping an EventHub
     * ====================
     * EventHub::Dispose() should be called to clean up after an event hub. Disposal will occur asynchronously.
     * EventHub::IsFullyDisposed() can be polled to determine whether the EventHub disposal is complete. The
     * destructor of EventHub will also initiate a Dispose().
     *
     * Failure to dispose of an EventHub will result in resource leaks.
     *
     * Registering and Unregistering Modules
     * =====================================
     * EventHub::RegisterModule() can be called to register modules with an EventHub. @see Module
     *
     * Module::UnregisterModule() can be called to unregister modules. @see Module
     *
     * Threading
     * =========
     * All public EventHub or Module methods can be safely invoked from any thread.
     *
     * For a given module, the OnRegistered and OnUnregistered callbacks of a module and its processors,
     * listeners, and dispatchers, as well as ModuleEventProcessor::Process and ModuleEventListener::Hear can often
     * be treated as if they operated on a single thread. These methods will never get invoked concurrently for
     * a given module.
     *
     * This allows most modules to be written without the use of synchronization primitives.
     *
     * An additional consideration for implementers is that callbacks should not perform long-running operations,
     * as these may block the system as a whole.
     *
     * Threading in Detail
     * ===================
     * This section covers the current implementation, which may change in the future, but may be informative for
     * module implementers.
     *
     * Upon creation, the EventHub starts a background thread (known as the EventHub thread).
     *
     * Some EventHub and Module methods require callbacks to be invoked. For example, Module::RegisterListener must
     * invoke the callback ModuleEventListener::OnRegistered after registration completes. In these cases, callbacks are
     * added to a callback queue. For example, after performing registration Module::RegisterListener will add
     * ModuleEventListener::OnRegistered to the callback queue. The EventHub thread monitors the callback queue.
     * When new callbacks are added to the queue, the EventHub thread empties the callback queue and executes the
     * callbacks synchronously on the background thread.
     *
     * Similarly, when Dispatch(event) is called, an event is placed on an event queue. After processing any callbacks,
     * the EventHub thread removes next event from the event queue then:
     * - Invokes any registered processors. Processors are invoked in no particular order and are invoked
     *   synchronously, in-series.
     * - Invoke registered listeners in parallel. Asynchronous jobs are started for each listener. Before
     *   moving on to the next event or callback, the EventHub waits for the asynchronous jobs to complete.
     *
     * Finally, upon disposal, all modules (and their child listeners, dispatchers, and processors) are unregistered
     * and thread is terminated.
     */
    class EventHub : public Object {
        friend class Module;
        friend class RuleTokenParser;
        friend class EventHubMethods; // For testing

    public:

        /**
         * Creates and returns a new EventHub.
         *
         * When the EventHub is no longer needed, EventHub::Dispose() must be called to free up resources used by the EventHub.
         *
         * @param name - the name of the EventHub to be created - for logging purposes
         * @param platform_services - instance of <code>PlatformServices</code> class to provide platform-specific functionality
         */
        static std::shared_ptr<EventHub> Create(const std::string& name,
                                                const std::shared_ptr<PlatformServicesInterface>& platform_services);

        /**
         * This method should be called after all modules are registered.
         * This will trigger the dispatch of a booted event.
         */
        virtual void FinishModulesRegistration() = 0;

        /**
         * Dispatches an event onto the event queue.
         *
         * Most modules should not call this method directly and should instead define a
         * subclass of ModuleEventDispatcher.
         *
         * @param event - the event to be added to the queue
         * @see ModuleEventDispatcher
         */
        virtual void Dispatch(const std::shared_ptr<Event>& event) = 0;

        /**
         * Creates and registers a module of the specified type.
         *
         * TModule must a subclass of Module.
         *
         * Example:
         *
         *     class MyModule : public Module { ... };
         *
         *     void RegisterMyModule(const std::shared_ptr<EventHub>& event_hub) {
         *         event_hub->RegisterModule<MyModule>();
         *     }
         */
        template<class TModule>
        void RegisterModule();

        /**
         * Creates and registers an ExternalModule
         *
         * Example:
         *
         *     std::shared_ptr<ExternalModuleInterface>& mod; // created by the Core
         *     RegisterExternalModule(mod);
         */
        virtual void RegisterExternalModule(const std::shared_ptr<ExternalModuleInterface>& external_module) = 0;

        /**
         * Check whether the name matches a module in the currently active modules list.
         */
        virtual bool IsRegisteredModule(const std::string& name) = 0;

        /**
         * Registers a one-time listener to modules of the specified type.
         *
         * TModule must be a subclass of Module.
         *
         * Example:
         *
         *     class MyModule : public Module { ... };
         *
         *     void RegisterOneTimeListenerToMyModule(const std::shared_ptr<EventHub>& event_hub
         *                                            EventType event_type, EventSource event_source, const std::string& pair_id,
         *                                            const std::function<void(const std::shared_ptr<Event>&)>& listener_block) {
         *         event_hub->RegisterOneTimeListener<MyModule>(event_type, event_source, pair_id, listener_block);
         *     }
         *
         * @param event_type - the EventType of an event to listen for
         * @param event_source - the EventSource of an event to listen for
         * @param pair_id - pairID to listen for
         * @param listener_block - the block to call when the event is heard
         */
        template<class TModule>
        void RegisterOneTimeListener(const std::shared_ptr<EventType>& event_type,
                                     const std::shared_ptr<EventSource>& event_source,
                                     const std::string& pair_id,
                                     const std::function<void(const std::shared_ptr<Event>&)>& listener_block);

        template<class TModule>
        void RegisterOneTimeListener(const std::shared_ptr<EventType>& event_type,
                                     const std::shared_ptr<EventSource>& event_source,
                                     const std::function<void(const std::shared_ptr<Event>&)>& listener_block);

        /**
         * Calls Dispose with a reasonable default wait time.
         */
        virtual bool Dispose() = 0;

        /**
         * Frees resources used by this, waiting up to `max_wait_duration` for the operation to complete.
         *
         * After calling Dispose(), most EventHub methods will have no effect.
         *
         * Calling Dispose() first triggers clean up to occur asynchronously. A number of actions will occur:
         * - Events will stop firing, but a few events may still fire after Dispose() is called due to race conditions.
         * - Modules, listeners, processors, and dispatchers will be unregistered.
         * - Threads and other resources used by the EventHub will be terminated.
         *
         * After triggering the asynchronous disposal, this call will block for up to `max_wait_duration` for the
         * operation to complete.
         *
         * @param max_wait_duration - the maximum duration to block this call while waiting for cleanup to complete.
         *                            A `0` time indicates that we will return immediately.
         *
         * @see IsFullyDisposed()
         *
         * @return true if the event hub is fully disposed (background thread shut down,
         * and all modules unregistered in background thread).
         */
        virtual bool Dispose(std::chrono::milliseconds max_wait_duration) = 0;

    protected:
        EventHub() {}

        /**
         * @private
         *
         * Calls Module::OnEventHubRegisteredModule()
         */
        static void CallModuleOnEventHubRegisteredModule(const std::shared_ptr<Module>& module,
                const std::shared_ptr<EventHub>& parent_hub,
                const std::shared_ptr<PlatformServicesInterface>& platform_services,
                const std::shared_ptr<TaskExecutorInterface>& task_executor);

        /**
         * @private
         *
         * Calls Module::Idle()
         */
        static void CallModuleIdle(const std::shared_ptr<Module>& module);

        /**
         * @private
         *
         * Calls Module::ProcessEvent()
         */
        static bool CallModuleProcessEvent(const std::shared_ptr<Module>& module,
                                           const std::shared_ptr<Event>& event,
                                           std::shared_ptr<Event>& processed_event);

        /**
         * @private
         *
         * Calls Module::NotifyListeners()
         */
        static void CallModuleNotifyListeners(const std::shared_ptr<Module>& module,
                                              const std::shared_ptr<Event>& event);

        /**
         * @private
         *
         * Calls Module::GetSharedStateName();
         */
        static std::string CallModuleGetSharedStateName(const std::shared_ptr<Module>& module);

        /**
         * @private
         *
         * Calls Module::UnregisterModule();
         */
        static void CallModuleUnregisterModule(const std::shared_ptr<Module>& module);

        /**
         * @private
         *
         * Calls Module::RegisterOneTimeListenerBlock();
         */
        static void CallModuleRegisterOneTimeListener(const std::shared_ptr<Module>& module,
                const std::shared_ptr<EventType>& event_type,
                const std::shared_ptr<EventSource>& event_source,
                const std::string& pair_id,
                const std::function<void(const std::shared_ptr<Event>&)>& listener_block);

    private:
        /**
         * @private
         *
         * Register a module after creation. Intended for use by RegisterModule<TModule>(...).
         */
        virtual void RegisterModule(const std::shared_ptr<Module>& module) = 0;

        /**
         * @private
         *
         * Register a rule for a given module.  Intended for use by RegisterRule<TModule>(...).
         */
        virtual void RegisterRule(const std::shared_ptr<Module>& module, const std::shared_ptr<Rule>& rule) = 0;

        /**
         * @private
         *
         * Unregisters all rules for a given module, Intended for use by UnregisterRules<TModule>(...).
         */
        virtual void UnregisterAllRules(const std::shared_ptr<Module>& module) = 0;

        /**
         * @private
         *
         * Perform book-keeping after a Module is unregistered. Intended for use by Module.
         */
        virtual void OnModuleUnregistered(const std::shared_ptr<Module>& module) = 0;

        /**
         * @private
         *
         * Register a one-time listener to the module who's type id matches the given hash.
         * Intented to be called by RegisterOneTimeListener<TModule>(...).
         */
        virtual void RegisterOneTimeListener(const size_t module_type_hash,
                                             const std::shared_ptr<EventType>& event_type,
                                             const std::shared_ptr<EventSource>& event_source,
                                             const std::string& pair_id,
                                             const std::function<void(const std::shared_ptr<Event>&)>& listener_block) = 0;

        /**
         * @private
         *
         * Creates a shared state object for the given module versioned at the current event for this hub.
         *
         * Only for use by Module.
         *
         * @param module  Module that owns this shared state
         * @param version int32_t containing the version that this shared state should be begin to be valid for
         * @param state   EventData object containing the state to share. Must be data, EventHub::PENDING, or EventHub::INVALID.
         *
         * @throws ErrorCodes::INVALID_ARGUMENT if the provided module is nullptr
         **/
        virtual void CreateSharedState(const std::shared_ptr<Module>& module,
                                       int32_t version,
                                       const std::shared_ptr<EventData>& state) = 0;

        /**
         * @private
         * Updates an existing EventHub::PENDING shared state for the given module and version
         *
         * Only for use by Module.
         *
         * @param module  Module to update the shared state for
         * @param version int32_t version version of the existing shared state to replace
         * @param state   new state to replace with existing state. Must be data, EventHub::PENDING, EventHub::INVALID,
         *          EventHub::NEXT, or EventHub::PREV.
         *
         * @throws ErrorCodes::INVALID_ARGUMENT if the provided module is nullptr
         **/
        virtual void UpdateSharedState(const std::shared_ptr<Module>& module,
                                       int32_t version,
                                       const std::shared_ptr<EventData>& state) = 0;

        /**
         * @private
         *
         * Creates or updates a shared state object for the given module and version.
         * If no shared state exists for the module at the given version, then one is created with the given state.
         * If a shared state already exists for the module at the given version and the state
         * is EventHub::PENDING, then the state is updated with the given state.
         *
         * Only for use by Module.
         *
         * @param module  Module that owns this shared state
         * @param version int32_t version version of the existing shared state to add or replace
         * @param state   EventData object containing the state to share. Must be data, EventHub::PENDING, or EventHub::INVALID
         * when creating or data, EventHub::PENDING, EventHub::INVALID, EventHub::NEXT, or EventHub::PREV when updating
         *
         * @throws ErrorCodes::INVALID_ARGUMENT if the provided module is nullptr
         **/
        virtual void CreateOrUpdateSharedState(const std::shared_ptr<Module>& module,
                                               int32_t version,
                                               const std::shared_ptr<EventData>& state) = 0;

        /**
         * @private
         *
         * Creates a shared state object for the given module at the next event number for this hub.
         *
         * Only for use by Module.
         *
         * @param module  Module that owns this shared state
         * @param state   EventData object containing the state to share. Must be data, EventHub::PENDING, or EventHub::INVALID.
         *
         * @throws ErrorCodes::INVALID_ARGUMENT if the provided module is nullptr
         **/
        virtual void CreateOrUpdateSharedState(const std::shared_ptr<Module>& module,
                                               const std::shared_ptr<EventData>& state) = 0;

        /**
         * @private
         * Clears all the shared states for the given module.
         *
         * Only for use by Module.
         *
         * @param module  Module to clear the shared states for
         *
         * @throws ErrorCodes::INVALID_ARGUMENT if the provided module is nullptr
         **/
        virtual void ClearSharedStates(const std::shared_ptr<Module>& module) = 0;

        /**
         * @private
         * Retrieves shared state by name that is valid for the given event
         *
         * Only for use by Module.
         *
         * @param state_name    String identifier for the module that shared the state
         * @param event         Event to retrieve state for
         * @param calling_module the module calling this method
         *
         * @return EventData object containing the valid state, EventHub::PENDING, or EventHub::INVALID
         * @throws ErrorCodes::INVALID_ARGUMENT if given event is nullptr
         **/
        virtual std::shared_ptr<EventData> GetSharedEventState(const std::string& state_name,
                const std::shared_ptr<Event>& event,
                const std::shared_ptr<Module>& calling_module) = 0;

        /**
         * @private
         * Determine if there are any shared states for the specified module.
         * A module is considered to have a valid shared state if any state is data or EventHub::PENDING.
         * States EventHub::INVALID, EventHub::NEXT, and EventHub::PREV are not considered valid.
         *
         * Only for use by Module.
         *
         * @param state_name    String identifier for the module that shared the state
         * @return true if the specified module has shared a valid state
         */
        virtual bool HasSharedEventState(const std::string& state_name) = 0;

        /**
         * @private
         *
         * Requests that Idle() be called soon. Intended for use by Module.
         *
         * This method may be called from any thread.
         */
        virtual void RequestIdle() = 0;

    };
}

/////////////////////////////////
// template/inline definitions //
/////////////////////////////////

namespace AdobeMarketingMobile {

    template<class TModule>
    void EventHub::RegisterModule() {

        // If you get an error on the following line, you need to make sure the type you pass
        // into RegisterModule is a subclass of Module.
        static_assert(std::is_base_of<Module, TModule>::value, "Type of TModule must be derived from Module.");

        // module registration is spread across multiple functions and threads
        // to find all the steps, search for "module registration step"

        // module registration step 1: construct the module
        auto module = std::make_shared<TModule>();

        // module registration step 2: pass it to the non-templated RegisterModule
        RegisterModule(module);
    }

    template<class TModule>
    void EventHub::RegisterOneTimeListener(const std::shared_ptr<EventType>& event_type,
                                           const std::shared_ptr<EventSource>& event_source, const std::string& pair_id,
                                           const std::function<void(const std::shared_ptr<Event>&)>& listener_block) {

        // If you get an error on the following line, you need to make sure the type you pass
        // into RegisterOneTimeListener is a subclass of Module.
        static_assert(std::is_base_of<Module, TModule>::value, "Type of TModule must be derived from Module.");

        size_t type_hash = typeid(TModule).hash_code();

        RegisterOneTimeListener(type_hash, event_type, event_source, pair_id, listener_block);
    }

    template<class TModule>
    void EventHub::RegisterOneTimeListener(const std::shared_ptr<EventType>& event_type,
                                           const std::shared_ptr<EventSource>& event_source,
                                           const std::function<void(const std::shared_ptr<Event>&)>& listener_block) {

        // If you get an error on the following line, you need to make sure the type you pass
        // into RegisterOneTimeListener is a subclass of Module.
        static_assert(std::is_base_of<Module, TModule>::value, "Type of TModule must be derived from Module.");

        size_t type_hash = typeid(TModule).hash_code();

        RegisterOneTimeListener(type_hash, event_type, event_source, "", listener_block);
    }
}

#endif //ADOBEMOBILE_CORE_EVENTHUB_H

