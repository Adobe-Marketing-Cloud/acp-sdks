/*
Copyright 2017 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_CORE_ONETIMELISTENER_H
#define ADOBEMOBILE_CORE_ONETIMELISTENER_H

#include <functional>
#include "ModuleEventListenerBase.h"

namespace AdobeMarketingMobile {
    class Module;

    /**
     * @class OneTimeListener
     * Used to wrap an OneTimeListenerBlock in an EventListener so it can be added to an EventHub.
     *
     * Do not use directly. @see EventHub::RegisterOneTimeListener.
     */
    class OneTimeListener : public ModuleEventListenerBase {
        friend class Module;

    public:
        /**
         * @see ModuleEventListenerBase::Hear
         */
        void Hear(const std::shared_ptr<Event>& event) override final;

        /**
         * Constructor.
         * For use by EventHub.
         */
        explicit OneTimeListener(const std::function<void(const std::shared_ptr<Event>&)>& block);

    private:
        /**
         * @private
         * the block this listener should execute.
         */
        std::function<void(const std::shared_ptr<Event>&)> block_;
    };
}

#endif //ADOBEMOBILE_CORE_ONETIMELISTENER_H
