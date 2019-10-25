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

#ifndef ADOBEMOBILE_CORE_INTERNALMODULE_H
#define ADOBEMOBILE_CORE_INTERNALMODULE_H

#include "Module.h"

namespace AdobeMarketingMobile {
    /**
     * @class InternalModule
     *
     * Base class for internal (Adobe only) defined modules. Calling Module::GetPlatformServices() on an
     * InternalModule allows access to platform-specific functionality in the environment owning the Module.
     */
    class InternalModule : public Module {
    protected:
        /**
         * Constructor.
         *
         * Subclasses should call this constructor to initialize the InternalModule.
         *
         * @param log_prefix - the name of the module
         */
        explicit InternalModule(const std::string& log_prefix);

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
    };
}

#endif //ADOBEMOBILE_CORE_INTERNALMODULE_H
