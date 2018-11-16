/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe Systems Incorporated
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

#ifndef ADOBEMOBILE_CORE_MODULE_H
#define ADOBEMOBILE_CORE_MODULE_H

#include <deque>
#include <map>
#include <string>
#include <thread>
#include <vector>
#include "Common.h"
#include "EventType.h"
#include "EventSource.h"
#include "Expected.h"
#include "Object.h"

namespace AdobeMarketingMobile {
    class Event;
    class EventData;
    class EventHub;
    class Rule;
    class InternalModule;
    class ModuleEventDispatcherBase;
    class ModuleEventListenerBase;
    class ModuleEventProcessorBase;
    class ModuleTaskOptions;
    class PlatformServicesInterface;
    class TaskExecutorInterface;
    enum class ModuleState : int32_t;

    // TODO: (AMSDK-5893) does InternalModule make sense anymore given our current external module design?

    /**
     * @class Module
     *
     * Module is the base class for modules.
     *
     * Quick Start
     * ===========
     * To create a module, derive from `Module` or `InternalModule` (for modules created internally):
     *
     *     class MyModule : public Module {
     *     public:
     *         // Subclasses must have a default constructor:
     *         MyModule() : Module{ "MyModule" } {} // "MyModule" is the log prefix
     *
     *         void OnRegistered() override {
     *             // ... perform initialization ...
     *         }
     *
     *         void OnUnregistered() override {
     *             // ... perform cleanup ...
     *         }
     *     };
     *
     * To register a module, call EventHub::RegisterModule():
     *
     *   std::shared_ptr<EventHub> event_hub = ...;
     *   event_hub->RegisterModule<MyModule>();
     *
     * Module Registration and Initialization
     * ======================================
     * EventHub::RegisterModule() can be used to register a module.
     *
     * Registration completes asynchronously. After EventHub::RegisterModule(), the following occurs:
     *
     *   1) The event hub constructs an instance of the module using its default constructor
     *      (i.e. `MyModule::MyModule()`). During the constructor, the module is not yet registered with the EventHub
     *      and therefore cannot register listeners, dispatchers, or processors.
     *
     *   2) The event hub invokes `Module::OnRegistered()` on the event hub thread. During `Module::OnRegistered()`,
     *      subclasses may register listeners, dispatchers, or processors.
     *
     * The following is an example of a module that performs some initialization:
     *
     *   class MyModule : public Module {
     *   public:
     *       MyModule() : Module{ "MyModule" },
     *            some_variable_{42} {
     *            // Some initialization can happen this method, BUT:
     *            //
     *            //   Do not call RegisterProcessor/RegisterListener/CreateDispatcher from the constructor. If called
     *            //   during the constructor, these methods will throw since the module does not have a reference to
     *            //   the EventHub yet. The same holds true for any calls that require an EventHub.
     *       }
     *
     *       void OnRegistered() override {
     *            // During this method, you will typically perform the bulk of your initialization.
     *            RegisterListener<MyModuleListener>(...);
     *            RegisterProcessor<MyModuleProcessor}>(...);
     *
     *            // You can also perform additional initialization in this method. HOWEVER, this method is invoked
     *            // in the eventloop and therefore should not perform long-running, synchronous operations.
     *       }
     *
     *   private:
     *       int32_t some_variable_;
     *   };
     *
     * Unregistering Modules
     * =====================
     * To register a module with EventHub, call `Module::UnregisterModule()`.
     *
     * After calling Module::UnregisterModule(), the following occurs:
     *
     *   1) The module drops pending, unstarted tasks and stops accepting new tasks. If a task was already started, it
     *      will be completed prior to invoking `Module::OnUnregistered()`. To schedule tasks that will be executed
     *      during unregistration (in order to peform blocking unregistration tasks) see Module::AddTaskToQueue().
     *
     *   2) The module unregisters all listeners, processors, and dispatchers and stops accepting new listeners,
     *      processors and dispatchers. As usual, the event hub invokes `OnUnregistered()` on the event hub thread for
     *      listeners, processors, and dispatchers registered by the module.
     *
     *   3) The event hub invokes `Module::OnUnregistered()` on the eventhub thread.
     *
     *   4) All remaining tasks (required for unregistartion) are completed and the background task thread is terminated.
     *
     *   5) The event hub and module release their references to eachother. At this time, the EventHub and Module
     *      may get destructed.
     *
     * Threading
     * =========
     * Module/listener/dispatcher/processor callbacks such as `OnRegistered()`, `OnUnregistered()`,
     * `ModuleEventListener::Hear()` and `ModuleEventProcessor::Process()` are called synchronously from the
     * event hub thread.
     *
     * This has a few consequences:
     *
     * 1) These methods will never be called concurrently and can be implemented as if they were executing on a single
     * thread.
     *
     * 2) These callbacks must NEVER perform blocking operations, as those will block the event hub.
     *
     * Additional details:
     * - Callbacks MAY be called concurrently for different Module instances.
     * - Modules should not expect that callbacks will be called from a specific thread or always be
     *   called from the same thread. The event hub may invoke these callbacks from any actual thread so long as
     *   the callbacks are invoked as if they originated from the same thread.
     */
    class Module : public Object {
        friend class EventHub; // EventHub should only access private methods marked for use by EventHub.
        friend class ModuleMethods; // For testing

    public:
        /**
         * Determines whether a module is currently registered.
         *
         * This method is thread-safe.
         *
         * NOTE: The result of this call be used as a hint. For threading reasons, it is possible
         * to become unregistered after IsRegistered() has already returned true.
         *
         * @returns true if this module is currently registered with an EventHub, false otherwise.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool IsRegistered();

        /**
         * Determines whether a module is an InternalModule.
         *
         * This method is thread-safe.
         *
         * @returns true if this module is an InternalModule, false otherwise.
         */
        bool IsInternal();

        /**
         * Get the name of this module
         *
         * @returns name of this module
         */
        std::string GetModuleName() const {
            return log_prefix_;
        }

    protected:
        /**
         * For convenience, a ModuleTaskOptions with `required_for_unregistration` set to true.
         */
        static const ModuleTaskOptions REQUIRED_FOR_UNREGISTRATION;

        /**
         * Constructor.
         *
         * Subclasses should call this constructor to initialize the InternalModule.
         *
         * @param log_prefix - the name of the module
         */
        explicit Module(const std::string& log_prefix);

        /**
         * Creates, registers, and returns an event dispatcher for this module.
         *
         * TDispatcher is the class of the dispatcher to create. TDispatcher should extend ModuleEventDispatcher<TModule>,
         * where TDispatcher is the type of the current module. In rare cases, TDispatcher may extend ModuleEventDispatcherBase
         * directly.
         *
         * This method will only have an effect while the Module is registered. Calling this method before
         * the Module is registered or after it is unregistered will be a noop.
         *
         * This method is thread-safe.
         *
         * @return a TDispatcher registered with the current module and eventhub
         *
         * @see ModuleEventDispatcher
         */
        template<class TDispatcher>
        std::shared_ptr<TDispatcher> CreateDispatcher();

        /**
         * This method is invoked shortly after the Module is registered.
         *
         * Subclasses may override this method to perform initialization tasks. Methods that require
         * an event hub (i.e. `RegisterListener()`)  may be safely invoked during this method.
         *
         * Threading
         * =========
         * Do not perform blocking operations during this method. Consider moving these operations to a
         * background thread.
         *
         * @see Module for additional threading information.
         *
         * Ordering
         * ========
         * This method is guaranteed to be called once, asynchronously, after EventHub::RegisterModule<TModule>()
         * is called. This call is guaranteed to occur prior to Module::OnUnregistered, ModuleEventListener callbacks,
         * and ModuleEventProcessor callbacks.
         */
        virtual void OnRegistered();


        /**
         * This method is invoked shortly before the Module is fully unregistered.
         *
         * Subclasses may override this method to perform cleanup tasks. Subclasses should
         * minimize the amount of cleanup performed in the destructor and should instead prefer to
         * perform cleanup in OnUnregistered().
         *
         * Threading
         * =========
         * Do not perform blocking operations during this method. Consider moving these operations to a
         * background thread.
         *
         * @see Module for threading guarantees.
         *
         * Ordering
         * ========
         * This method is guaranteed to be called once, asynchronously, after Module::UnregisterModule()
         * is called. This function is guaranteed to be called after pending Module callbacks, ModuleEventListener callbacks,
         * and ModuleEventProcessor callbacks. All pending tasks are guaranteed to be complete or cancelled before this
         * function is called (except tasks scheduled with `options.required_for_unregistration` set to true, which
         * may complete after this function is called). After calling this method, Module and its child objects will
         * receive no additional callbacks, and the EventHub will release any references to the Module and its child
         * objects.
         */
        virtual void OnUnregistered();

        /**
         * Registers an event processor for this module.
         *
         * Processors can process all events, not only events destined for the registering module
         *
         * TProcessor is the class of the processor to create. TProcessor should extend ModuleEventProcessor<TModule>,
         * where TProcessor is the type of the current module. In rare cases, TProcessor may extend ModuleEventProcessorBase
         * directly.
         *
         * This method is thread-safe.
         *
         * This method will only have an effect while the Module is registered. Calling this method before
         * the Module is registered or after it is unregistered will be a noop.
         *
         * @see ModuleEventProcessor
         */
        template<class TProcessor>
        void RegisterProcessor();

        /**
         * Registers an event listener for this module.
         *
         * Only one listener per type/source pair is allowed per module. Any collisions will be resolved by replacing
         * the existing listener with the new listener.
         *
         * TListener is the class of the listener to create. TListener should extend ModuleEventListener<TModule>,
         * where TModule is the type of the current module. In rare cases, TListener may extend ModuleEventListenerBase
         * directly.
         *
         * This method will only have an effect while the Module is registered. Calling this method before
         * the Module is registered or after it is unregistered will be a noop.
         *
         * Threading
         * =========
         * This method is thread-safe.
         *
         * Due to threading, it is possible (but rare) for existing listeners on event_type/event_source to get invoked slightly after
         * calling this function. For stricter ordering guarantees, Modules should override ModuleEventListener::OnUnregistered
         * and ModuleEventListener::OnRegistered.
         *
         * @param event_type - EventType to listen for
         * @param event_source - EventSource to listen for
         *
         * @see ModuleEventListener
         */
        template<class TListener>
        void RegisterListener(const std::shared_ptr<EventType>& event_type, const std::shared_ptr<EventSource>& event_source);

        /**
         * Registers a wild card event listener for this module.
         *
         * The wild card listener will receive all events that are dispatched by the event hub.
         * Internally, this method uses the {@link #registerListener(EventType, EventSource, Class)} to register an event listener
         * for {@link EventType#WILDCARD} and {@link EventSource#WILDCARD}.
         *
         */
        template<class TListener>
        void RegisterWildCardListener();

        /**
         * This method is not used, keeping it for compatibility reasons
         */
        ADOBE_VIRTUAL_FOR_TESTS void RegisterOneTimeListenerBlock(const std::shared_ptr<EventType>& type,
                const std::shared_ptr<EventSource>& source,
                const std::string& pair_id,
                const std::function<void(const std::shared_ptr<Event>&)>& block);

        /**
         * Unregisters this module from the parent event hub.
         *
         * This method is thread-safe.
         *
         * Due to threading, it is possible for listeners and processors to get invoked slightly after
         * calling this function. For stricter ordering guarantees, Modules should override OnUnregistered.
         */
        ADOBE_VIRTUAL_FOR_TESTS void UnregisterModule();

        /**
         * Unregisters a listener that matches the provided type/source
         *
         * Threading
         * =========
         * This method is thread-safe.
         *
         * Due to threading, it is possible (but rare) for removed listeners to get invoked slightly after
         * calling this function. For stricter ordering guarantees, Modules should override
         * ModuleEventListener::OnUnregistered.
         *
         * @param type - event type of listener to unregister
         * @param source - event source of listener to unregister
         */
        ADOBE_VIRTUAL_FOR_TESTS void UnregisterListener(const std::shared_ptr<EventType>& type,
                const std::shared_ptr<EventSource>& source);

        /**
         * Unregisters a wild card listener that was registered earlier.
         *
         * @see {@link RegisterWildcardListener}
         */
        ADOBE_VIRTUAL_FOR_TESTS void UnregisterWildCardListener();

        /**
         * Add a task to the module's thread pool that will be executed asynchronously.
         *
         * Equivalent to:
         *
         *     this->AddTaskToQueue(task_name, task_callback, ModuleTaskOptions{});
         *
         * @see `void AddTaskToQueue(const std::string& task_name, std::function<void()> task_callback, const ModuleTaskOptions& options )`
         */
        ADOBE_VIRTUAL_FOR_TESTS void AddTaskToQueue(const std::string& task_name,
                std::function<void()> task_callback);

        /**
         * Add a task to the module's thread pool that will be executed asynchronously.
         *
         * Calling this method during a Module's constructor is a noop.
         *
         * Threading
         * =========
         * This method is thread-safe.
         *
         * This method will capture a reference to the calling Module to keep it alive while running the task.
         *
         * Tasks from a given Module will be started and completed in FIFO order. For example:
         *
         *     AddTaskToQueue("a", [=] { Log::Debug("hello"); });
         *     AddTaskToQueue("b", [=] { Log::Debug("world"); });
         *
         * The above code will always print "hello" then "world". Task "b" will not start until task "a" completes.
         *
         * Unregistration
         * ==============
         * By default, pending, unstarted tasks will be cancelled when `Module::UnregisterModule()` is called.
         * If a task is in progress at the time `Module::UnregisterModule()` was called, it will be completed prior
         * to calling `Module::OnUnregistered`.
         *
         * To schedule tasks that can execute during/after unregistration, set `options.required_for_unregistration` to
         * true. Tasks scheduled in this manner will not be cancelled when `Module::UnregisterModule()` is called. Thus,
         * such tasks can execute after `Module::UnregisterModule()` and `Module::OnUnregistered()`.
         *
         * After `Module::OnUnregistered()` is called, no additional tasks may be scheduled regardless of the value of
         * `options.required_for_unregistration`. However, pending unregistration tasks that were scheduled prior to
         * `Module::OnUnregistered()` will be allowed to complete before fully unregistering the module and may
         * start and/or complete after `Module::OnUnregistered()`.
         *
         * @param task_name - the name of task to execute (can be empty)
         * @param task_callback - the task to execute
         * @param options - additional options for this task
         */
        ADOBE_VIRTUAL_FOR_TESTS void AddTaskToQueue(const std::string& task_name,
                std::function<void()> task_callback,
                const ModuleTaskOptions& options);

        /**
         * Creates a shared state for this module versioned at the current event count of the registering hub
         *
         * @param state   EventData object containing the state to save (can be nullptr)
         * @param version int containing the version that this shared state should be begin to be valid for
         **/
        ADOBE_VIRTUAL_FOR_TESTS void CreateSharedState(int32_t version, const std::shared_ptr<EventData>& state);

        /**
         * Updates an existing shared state for this module
         *
         * @param version   version of the existing shared state to replace
         * @param state     new state to replace with existing state
         **/
        ADOBE_VIRTUAL_FOR_TESTS void UpdateSharedState(int32_t version, const std::shared_ptr<EventData>& state);

        /**
         * Creates or updates a shared state for this module versioned at the current event count of the registering hub.
         *
         * @param state   EventData object containing the state to save (can be nullptr)
         * @param version version this shared state will be valid for
         **/
        ADOBE_VIRTUAL_FOR_TESTS void CreateOrUpdateSharedState(int32_t version, const std::shared_ptr<EventData>& state);

        /**
         * Creates a shared state for this module versioned at the next event count of the registering hub
         *
         * @param state   EventData object containing the state to save (can be nullptr)
         **/
        ADOBE_VIRTUAL_FOR_TESTS void CreateOrUpdateSharedState(const std::shared_ptr<EventData>& state);

        /**
         * Clear all the shared states that exist for this module
         *
         **/
        ADOBE_VIRTUAL_FOR_TESTS void ClearSharedStates();

        /**
         * Retrieves the named shared state that is valid for the given event
         *
         * @param state_name name of the shared state to retrieve
         * @param event     event to retrieve named state
         *
         * @return EventData object containing the valid state
         **/
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<EventData> GetSharedEventState(const std::string& state_name,
                const std::shared_ptr<Event>& event);

        /**
         * Determines if the named module contains any valid shared states.
         *
         * @param state_name name of the module to query for valid states
         *
         * @return true if the named module contains any valid shared states
         **/
        ADOBE_VIRTUAL_FOR_TESTS bool HasSharedEventState(const std::string& state_name);

        /**
         * Retrieve the unique module name for storing shared state information.
         *
         * @return String containing the container name for shared state for this module (can be empty string)
         *
         * ===================================================
         * Example override
         * ===================================================
         *
         *   std::string Audience::GetSharedStateName() {
         *       return EventDataKeys::Audience::SHARED_STATE_NAME;
         *   }
         *
         **/
        virtual std::string GetSharedStateName() = 0;

        /**
         * Gets the platform services.
         *
         * @return the platform services instance only if this is an internal module and is currently registered.
         * otherwise, returns nullptr.
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<PlatformServicesInterface> GetPlatformServices();

        /**
         * Registers a rule to be executed by the eventhub
         *
         */
        ADOBE_VIRTUAL_FOR_TESTS void RegisterRule(const std::shared_ptr<Rule>& rule);

        /**
         * Unregisters all previously registered rules
         *
         */
        ADOBE_VIRTUAL_FOR_TESTS void UnregisterAllRules();

    private:

        /**
         * @private
         *
         * Called by EventHub to complete registration of this module. Called with the event hub lock held.
         */
        ADOBE_VIRTUAL_FOR_TESTS void OnEventHubRegisteredModule(const std::shared_ptr<EventHub>& parent_hub,
                const std::shared_ptr<PlatformServicesInterface>& platform_services,
                const std::shared_ptr<TaskExecutorInterface>& task_executor);

        /**
         * @private
         *
         * Called by EventHub to performs idle time operations (including invoking pending callbacks).
         *
         * THREADING: Idle(), ProcessEvent(), and NotifyListeners() should not be called concurrently.
         */
        ADOBE_VIRTUAL_FOR_TESTS void Idle();

        /**
         * @private
         *
         * Called by EventHub to synchronously invoke event processors.
         *
         * @return true if the event was processed and sets processed_event to the processed event.
         * @return false if the event was not processed and does not change the value of processed_event.
         *
         * THREADING: Idle(), ProcessEvent(), and NotifyListeners() should not be called concurrently.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool ProcessEvent(const std::shared_ptr<Event>& event, std::shared_ptr<Event>& processed_event);

        /**
         * @private
         *
         * Called by EventHub to synchronously invoke event listeners.
         *
         * THREADING: Idle(), ProcessEvent(), and NotifyListeners() should not be called concurrently.
         */
        ADOBE_VIRTUAL_FOR_TESTS void NotifyListeners(const std::shared_ptr<Event>& event);

        /**
         * @private
         *
         * Called by EventHub to synchronously invoke wildcard event listeners.
         *
         * THREADING: Idle(), ProcessEvent(), and NotifyWildCardListener() should not be called concurrently.
         */
        ADOBE_VIRTUAL_FOR_TESTS void NotifyWildCardListener(const std::shared_ptr<Event>& event);

        /**
         * Register a listener after creation. Intended for use by RegisterListener<>(...).
         */
        ADOBE_VIRTUAL_FOR_TESTS void RegisterListener(const std::shared_ptr<ModuleEventListenerBase>& listener,
                const std::shared_ptr<EventType>& event_type,
                const std::shared_ptr<EventSource>& event_source,
                const std::string& pair_id);

        /**
         * @private
         *
         * Register a dispatcher after creation. Intended for use by CreateDispatcher<>(...).
         */
        ADOBE_VIRTUAL_FOR_TESTS void RegisterDispatcher(const std::shared_ptr<ModuleEventDispatcherBase>& dispatcher);

        /**
         * @private
         *
         * Register a processor after creation. Intended for use by RegisterProcessor<>(...).
         */
        ADOBE_VIRTUAL_FOR_TESTS void RegisterProcessor(const std::shared_ptr<ModuleEventProcessorBase>& processor);

        /**
         * @private
         *
         * Enqueues a callback for execution in Idle(), ProcessEvent(), or NotifyListeners().
         * After enqueing a callback, EventHub::RequestIdle() should typically be called.
         *
         * @param guard - a lock that refers to mutex_. The method will acquire mutex_ if needed and upon exit, guard will hold mutex_.
         * @param callback - the callback to queue up
         */
        void EnqueueCallback(std::unique_lock<std::mutex>& guard, const std::function<void()>& callback);

        /**
         * @private
         *
         * Helper for DoCommonEventHubThreadWork().
         *
         * If unregistration was initiated, completes it (in the eventhub thread). Acquires and releases mutex_.
         */
        void CompleteUnregistrationIfNeeded();

        /**
         * @private
         *
         * Helper for CompleteUnregistration()
         */
        void CompleteUnregistrationIfNeeded_UNREGISTERING();

        /**
         * @private
         * Helper for CompleteUnregistration()
         */
        void CompleteUnregistrationIfNeeded_DISPOSING_EXECUTOR();

        /**
         * @private
         * Helper for CompleteUnregistrationIfNeeded()
         */
        void CompleteUnregistrationIfNeeded_COMPLETING_NORMAL_TASKS();

        /**
         * @private
         *
         * This method performs common work that should happen during Idle(), ProcessEvent(),
         * and NotifyListeners().
         *
         * It does the following:
         * - executes pending callbacks
         * - if needed, performs unregistration work
         *
         * When this function exits with `true`,
         * - `out_guard` will hold mutex_
         * - the Module is not unregistering and not unregistered
         * - `pending_callbacks_` will be empty
         * - the caller may continue normally
         *
         * When this function exits with `false`,
         * - the Module is unregistering or unregistered
         * - `out_guard` is unchanged
         * - `pending_callbacks_` will be empty
         * - the caller should return immediately since
         *
         * @param guard - on input, should be a default constructed `std::unique_lock<std::mutex>`
         */
        bool DoCommonEventHubThreadWork(std::unique_lock<std::mutex>& guard);

        /**
         * @private
         *
         * Main mutex for synchronization of Module.
         *
         * IMPORTANT: Be very very careful when calling external functions
         * while holding mutex_, especially if those functions acquire
         * mutexes. Failure to do this can result in hard-to-reproduce
         * deadlocks.
         *
         * The following are known mutex orderings of this class:
         * - EventHub::mutex_ BEFORE Module::mutex_
         */
        std::mutex mutex_;

        /**
         * @private
         * the log prefix for this module's logs
         */
        std::string log_prefix_;

        /**
         * @private
         *
         * The current state (registered, etc) of this.
         *
         * Synchronized on mutex_.
         */
        ModuleState state_;

        /**
         * @private
         *
         * the parent event hub.
         *
         * while the module is registered, this value should be non-null. this means that the parent event hub
         * is kept alive as along as this module is registered. this is done deliberately to allow the module
         * and child objects to make use of the event hub's background thread for callbacks. the reference cycle
         * is broken after the module is unregistered.
         *
         * synchronized on mutex_.
         */
        std::shared_ptr<EventHub> parent_hub_;

        /**
         * the currently registered dispatchers.
         * this variable ensures that ModuleEventDispatchers stay alive as long as their module is registered.
         *
         * synchronized on mutex_.
         */
        std::vector<std::shared_ptr<ModuleEventDispatcherBase>> dispatchers_;

        /**
         * the currently registered processors.
         * this variable ensures that ModuleEventProcessors stay alive as long as their module is registered.
         *
         * synchronized on mutex_.
         */
        std::vector<std::shared_ptr<ModuleEventProcessorBase>> processors_;

        /**
         * the currently registered listeners, may contain nullptr entries.
         *
         * using a shared_ptr value ensures that ModuleEventListeners stay alive as long as their module is registered.
         *
         * synchronized on mutex_.
         */
        std::map<std::tuple<EventType*, EventSource*, std::string>, std::shared_ptr<ModuleEventListenerBase>> listeners_;

        /**
         * the platform services instance.
         * may be null if the event hub was destructed or the module is unregistered.
         *
         * synchronized on mutex_.
         */
        std::weak_ptr<PlatformServicesInterface> platform_services_;

        /**
         * a queue of callbacks that need to be executed in Idle(), ProcessEvent(), or NotifyListeners().
         *
         * synchronized on mutex_.
         */
        std::deque<std::function<void()>> pending_callbacks_;

        /**
         * @private
         *
         * Task executor for this module.
         *
         * synchronized on mutex_.
         */
        std::shared_ptr<TaskExecutorInterface> task_executor_;

        /**
         * @private
         *
         * Is a task with `options.required_for_unregistration` set to false currently executing?
         *
         * synchronized on mutex_.
         */
        bool normal_task_is_executing_;
    };



    /**
     * Options for Module::AddTaskToQueue(). POD class.
     *
     * @see Module::AddTaskToQueue()
     */
    class ModuleTaskOptions {
    public:
        /**
         * If true, this task can execute after UnregisterModule() has been called.
         * If false, this task will be cancelled after UnregisterModule() (if it has not already started
         * and/or completed).
         *
         * @see Module::AddTaskToQueue()
         */
        bool required_for_unregistration = false;
    };

    /**
     * Namespace that contains SdkError codes. @see SdkError
     */
    namespace ErrorCodes {
        constexpr static const char* MODULE_INVALID_STATE =
                    "module.invalid_state"; ///< Module is in an invalid state to perform the desired operation
    }

}


/////////////////////////////////
// template/inline definitions //
/////////////////////////////////

namespace AdobeMarketingMobile {
    template<class TDispatcher>
    std::shared_ptr<TDispatcher> Module::CreateDispatcher() {
        // If you get an error on the following line, you need to make sure the type you pass
        // into CreateDispatcher is a subclass of ModuleEventDispatcherBase.
        static_assert(std::is_base_of<ModuleEventDispatcherBase, TDispatcher>::value,
                      "Type of TDispatcher must be derived from ModuleEventDispatcherBase.");

        static_assert(std::is_default_constructible<TDispatcher>::value, "TDispatcher must be default constructible.");
        auto instance = std::make_shared<TDispatcher>();
        RegisterDispatcher(instance);
        return instance;
    }

    template<class TProcessor>
    void Module::RegisterProcessor() {
        // If you get an error on the following line, you need to make sure the type you pass
        // into RegisterProcessor is a subclass of ModuleEventProcessorBase.
        static_assert(std::is_base_of<ModuleEventProcessorBase, TProcessor>::value,
                      "Type of TProcessor must be derived from ModuleEventProcessorBase.");

        static_assert(std::is_default_constructible<TProcessor>::value, "TProcessor must be default constructible.");
        RegisterProcessor(std::make_shared<TProcessor>());
    }

    template<class TListener>
    void Module::RegisterListener(const std::shared_ptr<EventType>& event_type,
                                  const std::shared_ptr<EventSource>& event_source) {
        // If you get an error on the following line, you need to make sure the type you pass
        // into RegisterListener is a subclass of ModuleEventListenerBase.
        static_assert(std::is_base_of<ModuleEventListenerBase, TListener>::value,
                      "Type of TListener must be derived from ModuleEventListenerBase.");

        static_assert(std::is_default_constructible<TListener>::value, "TListener must be default constructible.");
        RegisterListener(std::make_shared<TListener>(), event_type, event_source, std::string{});
    }

    template<class TListener>
    void Module::RegisterWildCardListener() {
        // If you get an error on the following line, you need to make sure the type you pass
        // into RegisterListener is a subclass of ModuleEventListenerBase.
        static_assert(std::is_base_of<ModuleEventListenerBase, TListener>::value,
                      "Type of TListener must be derived from ModuleEventListenerBase.");

        static_assert(std::is_default_constructible<TListener>::value, "TListener must be default constructible.");
        RegisterListener(std::make_shared<TListener>(), EventType::WILDCARD, EventSource::WILDCARD, std::string{});
    }

}

#endif //ADOBEMOBILE_CORE_MODULE_H
