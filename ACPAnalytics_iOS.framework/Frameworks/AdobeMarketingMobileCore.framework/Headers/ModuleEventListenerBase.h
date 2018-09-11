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

#ifndef ADOBEMOBILE_CORE_MODULEEVENTLISTENERBASE_H
#define ADOBEMOBILE_CORE_MODULEEVENTLISTENERBASE_H

#include "Common.h"
#include "Object.h"

namespace AdobeMarketingMobile {
    class Event;
    class Module;
    class EventType;
    class EventSource;

    /**
     * Base class for all event listeners. In most cases, subclasses should derive from
     * ModuleEventListener<TModule> instead of deriving from this class directly.
     *
     * @see ModuleEventListener
     */
    class ModuleEventListenerBase : public Object {
        friend class Module; // Module should only access private methods marked for use by Module.
        friend class ModuleEventListenerMethods; // For testing

    public:
        /**
         * @returns the event type this listener is listening for
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::shared_ptr<EventType>& GetEventType();

        /**
         * @returns the event source this listener is listening for
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::shared_ptr<EventSource>& GetEventSource();

        /**
         * Called when an event matching the EventType and EventSource of this listener is
         * received on the EventHub that this listener is registered with.
         *
         * @param event - the event that was received.
         */
        virtual void Hear(const std::shared_ptr<Event>& event) = 0;

        /**
         * @returns the parent module or nullptr if the parent module was destructed or unregistered.
         *
         * NOTE: In rare cases where this function is called concurrently with UnregisterModule, it is
         * possible for GetParentModule() to return a non-nullptr to an unregistered module.
         */
        std::shared_ptr<Module> GetParentModule();

        /**
         * @return true once this is registered and OnRegistered() is called.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool IsFullyRegistered();

        /**
         * @return true once this is unregistered and OnUnregistered() is called.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool IsFullyUnregistered();

    protected:
        /**
         * Constructor.
         * For use by subclasses.
         */
        ModuleEventListenerBase();

        /**
         * This method is invoked shortly after the listener is registered.
         *
         * Subclasses should override this method to perform initialization tasks. Subclasses should
         * minimize the amount of initialization performed in the constructor and should instead prefer to
         * perform initialization in OnRegistered().
         *
         * THREADING
         * =========
         * @see Module for threading guarantees.
         *
         * ORDERING
         * ========
         * This method is guaranteed to be called once, asynchronously, after Module::RegisterListener<TListener>()
         * is called. This call is guaranteed to occur after Module::OnRegistered
         * and before the ModuleEventListenerBase::Hear(...) is called
         */
        virtual void OnRegistered();

        /**
         * This method is invoked shortly before the listener is fully unregistered.
         *
         * Subclasses should override this method to perform cleanup tasks. Subclasses should
         * minimize the amount of cleanup performed in the destructor and should instead prefer to
         * perform cleanup in OnUnregistered().
         *
         * THREADING
         * =========
         * @see Module for threading guarantees.
         *
         * ORDERING
         * ========
         * This method is guaranteed to be called once, asynchronously, after the listener is
         * unregistered via Module::UnregisterListener(), Module::RegisterListener(), or
         * Module::UnregisterModule() is called. This call is guaranteed to occur before
         * Module::OnUnregistered.
         */
        virtual void OnUnregistered();

    private:
        /**
         * @private
         *
         * Called during creation to finish 2-phase initialization of this.
         * For use by Module only.
         * Made public for testing listener in isolation. In production treat as private access.
         */
        ADOBE_VIRTUAL_FOR_TESTS void Init(const std::shared_ptr<Module>& parent_module,
                                          const std::shared_ptr<EventType>& event_type,
                                          const std::shared_ptr<EventSource>& event_source);

        /**
         * @private
         *
         * Calls OnRegistered.
         *
         * For use by Module only.
         */
        ADOBE_VIRTUAL_FOR_TESTS void CallOnRegistered();

        /**
         * @private
         *
         * Calls OnUnregistered.
         *
         * For use by Module only.
         */
        ADOBE_VIRTUAL_FOR_TESTS void CallOnUnregistered();

        /**
         * @private
         *
         * @returns true if this is a one time listener
         * For use by Module only.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool IsOneTime();

        /**
         * @private
         *
         * Actual implementation of GetParentModule, present and virtual to enable mocking.
         *
         * @returns the parent module
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<Module> GetParentModuleImpl();

        /**
         * @private
         *
         * the parent module
         */
        std::weak_ptr<Module> parent_module_;

        /**
         * @private
         *
         * the event type this listener is listening for
         */
        std::shared_ptr<EventType> event_type_;

        /**
         * @private
         *
         * the event source this listener is listening for
         */
        std::shared_ptr<EventSource> event_source_;

        /**
         * @private
         *
         * is this a one time listener?
         */
        bool is_one_time_;

        /**
         * @private
         *
         * Set to true once this is fully registered (OnRegistered called).
         */
        std::atomic<bool> is_fully_registered_;

        /**
         * @private
         *
         * Set to true once this is fully unregistered (OnUnregistered called).
         */
        std::atomic<bool> is_fully_unregistered_;
    };
}

#endif //ADOBEMOBILE_CORE_MODULEEVENTLISTENERBASE_H
