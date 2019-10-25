/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_CORE_MODULEEVENTDISPATCHER_H
#define ADOBEMOBILE_CORE_MODULEEVENTDISPATCHER_H

#include "ModuleEventDispatcherBase.h"

namespace AdobeMarketingMobile {

    /**
     * @class ModuleEventDispatcher
     *
     * ModuleEventDispatcher is the base class for event dispatchers. ModuleEventDispatchers transform
     * module-specific data into Events and dispatch them on the event hub.
     *
     * The template argument, TModule, is the type of the Module. TModule must be a subclass of Module.
     *
     * Quick Start
     * ===========
     * To create a dispatcher, derive from ModuleEventDispatcher:
     *
     *     class MyDispatcher : public ModuleEventDispatcher<MyModule> {
     *     public:
     *         MyDispatcher() = default; // Subclasses must have a default constructor
     *
     *         void OnRegistered() override {
     *             // ... perform initialization ...
     *         }
     *
     *         void OnUnregistered() override {
     *             // ... perform cleanup ...
     *         }
     *
     *         // a module-specific method
     *         void SendMyEvent() {
     *             auto event = EventBuilder{"Configure with AppId", EventType::CONFIGURATION, EventSource::REQUEST_CONTENT}
     *                  .Build();
     *             Dispatch(event);
     *         }
     *     };
     *
     * To register a dispatcher, call Module::CreateDispatcher():
     *
     *     class MyModule : public Module {
     *         std::shared_ptr<MyDispatcher> my_dispatcher_;
     *
     *         void OnRegistered() override {
     *             my_dispatcher_ = CreateDispatcher<MyDispatcher>();
     *             my_dispatcher_->SendMyEvent();
     *         }
     *     };
     *
     * Registration
     * ============
     * Module::CreateDispatcher() can be used to create a dispatcher.
     *
     * Registration completes asynchronously. After Module::CreateDispatcher() is called,
     * ModuleEventDispatcher::OnRegistered() will be called asynchronously to notify the dispatcher that it is
     * registered. Subclasses should perform initialization within this method.
     *
     * Unregistration
     * ==============
     * A dispatcher can be unregistered in several different ways:
     *
     * - If a module is unregistered via Module::UnregisterModule(), all dispatchers for that module will be
     *   unregistered.
     *
     * - If EventHub::Dispose() is called, all modules and their dispatchers will be unregistered
     *
     * Unregistration completes asynchronously. ModuleEventDispatcher::OnUnregistered() will be called asynchronously
     * to notify the dispatcher that it is unregistered. Subclasses should perform cleanup within this method.
     *
     * Threading
     * =========
     * As with most module-related methods, ModuleEventDispatcher::OnRegistered() and
     * ModuleEventDispatcher::OnUnregistered(), will never be invoked concurrently with eachother or with other callbacks
     * for the same Module. Therefore, many listeners can be implemented as if they operated on a single thread.
     *
     * @see Module for additional threading information.
     *
     */
    template<class TModule>
    class ModuleEventDispatcher : public ModuleEventDispatcherBase {
        // If you get an error on the following line, you need to make sure that TModule is a type derived from Module.
        static_assert(std::is_base_of<Module, TModule>::value, "Type of TModule must be derived from Module.");

    public:
        /**
         * @returns the parent module or nullptr if the parent module was destructed or unregistered.
         *
         * NOTE: In rare cases where this function is called concurrently with UnregisterModule, it is
         * possible for GetParentModule() to return a non-nullptr to an unregistered module.
         *
         * Deliberately hides ModuleEventDispatcherBase::GetParentModule().
         */
        std::shared_ptr<TModule> GetParentModule();

    protected:
        /**
         * Constructor.
         * For use by subclasses.
         */
        ModuleEventDispatcher();
    };
}


/////////////////////////////////
// template/inline definitions //
/////////////////////////////////

namespace AdobeMarketingMobile {
    template<class TModule>
    ModuleEventDispatcher<TModule>::ModuleEventDispatcher() {}

    template<class TModule>
    std::shared_ptr<TModule>
    ModuleEventDispatcher<TModule>::GetParentModule() {
        return std::dynamic_pointer_cast<TModule>(ModuleEventDispatcherBase::GetParentModule());
    }
}

#endif //ADOBEMOBILE_CORE_MODULEEVENTDISPATCHER_H
