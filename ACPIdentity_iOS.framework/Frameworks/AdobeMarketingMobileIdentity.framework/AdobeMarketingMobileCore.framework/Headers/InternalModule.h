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
