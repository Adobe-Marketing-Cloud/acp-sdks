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

#ifndef ADOBEMOBILE_CORE_MODULEEVENTPROCESSOR_H
#define ADOBEMOBILE_CORE_MODULEEVENTPROCESSOR_H

#include "ModuleEventProcessorBase.h"

namespace AdobeMarketingMobile {

    /**
     * @class ModuleEventProcessor
     *
     * ModuleEventProcessor is the base class for event processors. ModuleEventProcessors can transform
     * or can events that are dispatched through the EventHub.
     *
     * The template argument, TModule, is the type of the Module. TModule must be a subclass of Module.
     *
     * Quick Start
     * ===========
     * To create a processor, derive from ModuleEventProcessor:
     *
     *     class MyModuleEventProcessor : public ModuleEventProcessor<MyModule> {
     *     public:
     *         MyModuleEventProcessor() = default; // Subclasses must have a default constructor
     *
     *         void OnRegistered() override {
     *             // ... perform initialization ...
     *         }
     *
     *         void OnUnregistered() override {
     *             // ... perform cleanup ...
     *         }
     *
     *         std::shared_ptr<Event> Process(const std::shared_ptr<Event>& event) override {
     *             // do something when event occurs
     *             // this example just forwards the event:
     *             return event
     *         }
     *     };
     *
     * To register a processor, call Module::RegisterProcessor():
     *
     *     class MyModule : public Module {
     *         void OnRegistered() override {
     *             RegisterProcessor<MyProcessor>();
     *         }
     *     };
     *
     * Registration
     * ============
     * Module::RegisterProcessor() can be used to register a processor for a given event type or event source.
     *
     * Registration completes asynchronously. After Module::RegisterProcessor() is called,
     * ModuleEventProcessor::OnRegistered() will be called asynchronously to notify the processor that it is
     * registered. Subclasses should perform initialization within this method.
     *
     * Processing Events
     * =================
     * When an event is dispatched, any registered processors will receive a chance to intercept and replace,
     * transform the event via ModuleEventProcessorBase::Process(). Subclasses should override this method.
     *
     * Unregistering a Processor
     * ========================
     * A processor can be unregistered in several different ways:
     *
     * - If a module is unregistered via Module::UnregisterModule(), all processors for that module will be
     *   unregistered.
     *
     * - If EventHub::Dispose() is called, all modules and their processors will be unregistered
     *
     * Unregistration completes asynchronously. ModuleEventProcessor::OnUnregistered() will be called asynchronously
     * to notify the processor that it is unregistered. Subclasses should perform cleanup within this method.
     *
     * Threading
     * =========
     * As with most module-related methods, ModuleEventProcessor::OnRegistered(), ModuleEventProcessor::OnUnregistered(),
     * and ModuleEventProcessor::Process() will never be invoked concurrently with eachother or with other callbacks
     * for the same Module. Therefore, many processors can be implemented as if they operated on a single thread.
     *
     * @see Module for additional threading information.
     *
     */
    template<class TModule>
    class ModuleEventProcessor : public ModuleEventProcessorBase {
        // If you get an error on the following line, you need to make sure that TModule is a type derived from Module.
        static_assert(std::is_base_of<Module, TModule>::value, "Type of TModule must be derived from Module.");

    public:
        /**
         * @returns the parent module or nullptr if the parent module was destructed or unregistered.
         *
         * NOTE: In rare cases where this function is called concurrently     with UnregisterModule, it is
         * possible for GetParentModule() to return a non-nullptr to an unregistered module.
         *
         * Deliberately hides ModuleEventProcessorBase::GetParentModule().
         */
        std::shared_ptr<TModule> GetParentModule();

    protected:
        /**
         * Constructor.
         * For use by subclasses.
         */
        ModuleEventProcessor();
    };
}

/////////////////////////////////
// template/inline definitions //
/////////////////////////////////

namespace AdobeMarketingMobile {
    template<class TModule>
    ModuleEventProcessor<TModule>::ModuleEventProcessor() {}

    template<class TModule>
    std::shared_ptr<TModule>
    ModuleEventProcessor<TModule>::GetParentModule() {
        return std::dynamic_pointer_cast<TModule>(ModuleEventProcessorBase::GetParentModule());
    }
}

#endif //ADOBEMOBILE_CORE_MODULEEVENTLISTENER_H
