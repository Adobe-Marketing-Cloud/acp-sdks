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

#ifndef ADOBEMOBILE_CORE_MODULEEVENTLISTENER_H
#define ADOBEMOBILE_CORE_MODULEEVENTLISTENER_H

#include "ModuleEventListenerBase.h"

namespace AdobeMarketingMobile {

    /**
     * @class ModuleEventListener
     *
     * ModuleEventListener is the base class for event listeners. ModuleEventListeners hear and react to Events
     * that are dispatched through the EventHub.
     *
     * The template argument, TModule, is the type of the Module. TModule must be a subclass of Module.
     *
     * Quick Start
     * ===========
     * To create a listener, derive from ModuleEventListener:
     *
     *     class MyListener : public ModuleEventListener<MyModule> {
     *     public:
     *         MyListener() = default; // Subclasses must have a default constructor
     *
     *         void OnRegistered() override {
     *             // ... perform initialization ...
     *         }
     *
     *         void OnUnregistered() override {
     *             // ... perform cleanup ...
     *         }
     *
     *         void Hear(const std::shared_ptr<Event>& event) override {
     *             // do something when event occurs
     *         }
     *     };
     *
     * To register a listener, call Module::RegisterListener():
     *
     *     class MyModule : public Module {
     *         void OnRegistered() override {
     *             RegisterListener<MyListener>(EventSource::SOME_VALUE, EventType::SOME_VALUE);
     *         }
     *     };
     *
     * Registration
     * ==============
     * Module::RegisterListener() can be used to register a listener for a given event type or event source.
     *
     * Registration completes asynchronously. After Module::RegisterListener() is called,
     * ModuleEventListener::OnRegistered() will be called asynchronously to notify the listener that it is
     * registered. Subclasses should perform initialization within this method.
     *
     * A module may only have a single listener for a given event type and source.
     *
     * Alternatively, one time listeners can be registered to react once to a single, specific event.
     * @see EventHub::RegisterOneTimeListener.
     *
     * Responding to Events
     * ====================
     * When an event is dispatched, any registered listeners will receive notification that the event occurred
     * via ModuleEventListenerBase::Hear(). Subclasses should override this method to react appropriately to
     * Events.
     *
     * Unregistration
     * ==============
     * A listener can be unregistered in several different ways:
     *
     * - Explicitly, via Module::UnregisterListener()
     *
     * - If a different listener is registered for the same event type and source, the old listener will be
     *   unregistered prior to registering the new listener.
     *
     * - If a module is unregistered via Module::UnregisterModule(), all listeners for that module will be
     *   unregistered.
     *
     * - If EventHub::Dispose() is called, all modules and their listeners will be unregistered
     *
     * Unregistration completes asynchronously. ModuleEventListener::OnUnregistered() will be called asynchronously
     * to notify the listener that it is unregistered. Subclasses should perform cleanup within this method.
     *
     * Threading
     * =========
     * As with most module-related methods, ModuleEventListener::OnRegistered(), ModuleEventListener::OnUnregistered(),
     * and ModuleEventListener::Hear() will never be invoked concurrently with eachother or with other callbacks
     * for the same Module. Therefore, many listeners can be implemented as if they operated on a single thread.
     *
     * @see Module for additional threading information.
     *
     */
    template<class TModule>
    class ModuleEventListener : public ModuleEventListenerBase {
        // If you get an error on the following line, make sure that TModule is a type derived from Module.
        static_assert(std::is_base_of<Module, TModule>::value, "Type of TModule must be derived from Module.");
    public:

        /**
         * @returns the parent module or nullptr if the parent module was destructed or unregistered.
         *
         * NOTE: In rare cases where this function is called concurrently with UnregisterModule, it is
         * possible for GetParentModule() to return a non-nullptr to an unregistered module.
         *
         * Deliberately hides ModuleEventListenerBase::GetParentModule().
         */
        std::shared_ptr<TModule> GetParentModule();

    protected:
        /**
         * Constructor.
         * For use by subclasses.
         */
        ModuleEventListener();
    };
}

/////////////////////////////////
// template/inline definitions //
/////////////////////////////////

namespace AdobeMarketingMobile {
    template<class TModule>
    ModuleEventListener<TModule>::ModuleEventListener() {}

    template<class TModule>
    std::shared_ptr<TModule>
    ModuleEventListener<TModule>::GetParentModule() {
        return std::dynamic_pointer_cast<TModule>(ModuleEventListenerBase::GetParentModule());
    }
}

#endif //ADOBEMOBILE_CORE_MODULEEVENTLISTENER_H
