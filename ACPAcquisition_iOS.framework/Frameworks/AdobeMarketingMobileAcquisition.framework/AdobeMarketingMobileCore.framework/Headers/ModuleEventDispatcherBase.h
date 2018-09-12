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

#ifndef ADOBEMOBILE_CORE_MODULEEVENTDISPATCHERBASE_H
#define ADOBEMOBILE_CORE_MODULEEVENTDISPATCHERBASE_H

#include "Common.h"
#include "Object.h"

namespace AdobeMarketingMobile {
    class Event;
    class EventHub;
    class Module;

    /**
     * Base class for all event dispatchers. In most cases, subclasses should derive from
     * ModuleEventDispatcher<TModule> instead of deriving from this class directly.
     */
    class ModuleEventDispatcherBase : public Object {
        friend class Module; // Module should only access private methods marked for use by Module.
        friend class ModuleEventDispatcherMethods; // For testing

    public:
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
        ModuleEventDispatcherBase();

        /**
         * Dispatches an event to the associated EventHub.
         *
         * @param event - the Event to dispatch
         */
        ADOBE_VIRTUAL_FOR_TESTS void Dispatch(const std::shared_ptr<Event>& event);

        /**
         * This method is invoked shortly after the dispatcher is registered.
         *
         * Subclasses should override this method to perform initialization tasks. Subclasses should
         * minimize the amount of initialization performed in the constructor and should instead prefer to
         * perform initialization in OnRegistered().
         *
         * Threading
         * =========
         * @see Module for threading guarantees.
         *
         * Ordering
         * ========
         * This method is guaranteed to be called once, asynchronously, after Module::CreateDispatcher<TDispatcher>()
         * is called. This call is guaranteed to occur after Module::OnRegistered.
         */
        virtual void OnRegistered();

        /**
         * This method is invoked shortly before the dispatcher is fully unregistered.
         *
         * Subclasses should override this method to perform cleanup tasks. Subclasses should
         * minimize the amount of cleanup performed in the destructor and should instead prefer to
         * perform cleanup in OnUnregistered().
         *
         * Threading
         * =========
         * @see Module for threading guarantees.
         *
         * Ordering
         * ========
         * This method is guaranteed to be called once, asynchronously, after Module::UnregisterModule()
         * is called. This call is guaranteed to occur before Module::OnUnregistered.
         */
        virtual void OnUnregistered();

    private:
        /**
         * @private
         * Called during creation to finish 2-phase initialization of this.
         * For use by Module only.
         */
        ADOBE_VIRTUAL_FOR_TESTS void Init(std::shared_ptr<Module> parent_module,
                                          const std::shared_ptr<EventHub>& event_hub);

        /**
         * @private
         * Calls OnRegistered.
         *
         * For use by Module only.
         */
        ADOBE_VIRTUAL_FOR_TESTS void CallOnRegistered();

        /**
         * @private
         * Calls OnUnregistered.
         *
         * For use by Module only.
         */
        ADOBE_VIRTUAL_FOR_TESTS void CallOnUnregistered();

        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<Module> GetParentModuleImpl();

        /**
         * @private
         * the parent module
         */
        std::weak_ptr<Module> parent_module_;

        /**
         * @private
         * the parent module's event hub
         */
        std::weak_ptr<EventHub> event_hub_;

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

#endif //ADOBEMOBILE_CORE_MODULEEVENTDISPATCHERBASE_H
