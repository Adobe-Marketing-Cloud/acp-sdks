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

#ifndef ADOBEMOBILE_CORE_ONETIMELISTENER_H
#define ADOBEMOBILE_CORE_ONETIMELISTENER_H

#include <functional>
#include "ModuleEventListenerBase.h"

namespace AdobeMarketingMobile {
    class Module;

    /**
     * @class OneTimeListener
     * Used to wrap a Module.OneTimeListenerBlock in an EventListener so it can be added to an EventHub.
     *
     * Do not use directly. @see Module::RegisterOneTimeListenerBlock.
     */
    class OneTimeListener : public ModuleEventListenerBase {
        friend class Module;

    public:
        /**
         * @see ModuleEventListenerBase::Hear
         */
        void Hear(const std::shared_ptr<Event>& event) override final;

    private:
        /**
         * @private
         * Constructor.
         * For use by Module only.
         */
        explicit OneTimeListener(const std::function<void(const std::shared_ptr<Event>&)>& block);

        /**
         * @private
         * the block this listener should execute.
         */
        std::function<void(const std::shared_ptr<Event>&)> block_;
    };
}

#endif //ADOBEMOBILE_CORE_ONETIMELISTENER_H
