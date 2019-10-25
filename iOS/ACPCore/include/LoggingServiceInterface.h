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

#ifndef ADOBEMOBILE_PLATFORMSHIM_LOGGINGSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_LOGGINGSERVICEINTERFACE_H

#include <string>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    class LoggingServiceInterface : public virtual ObjectInterface {
    public:
        /**
         * Information provided to the debug method should contain high-level details about the data being processed.
         *
         * @param	tag	the class or method tag associated with the message
         * @param	message	the string to be logged
         *
         */
        virtual void Debug(const std::string& tag, const std::string& message) const = 0;
        /**
         * Information provided to the warning method should contain high-level details about the data being processed.
         *
         * @param	tag	the class or method tag associated with the message
         * @param	message	the string to be logged
         *
         */
        virtual void Warning(const std::string& tag, const std::string& message) const = 0;
        /**
         * Information provided to the error method should contain high-level details about the data being processed.
         *
         * @param	tag	the class or method tag associated with the message
         * @param	message	the string to be logged
         *
         */
        virtual void Error(const std::string& tag, const std::string& message) const = 0;
        /**
         * Information provided to the trace method should contain high-level details about the data being processed.
         *
         * @param    tag    the class or method tag associated with the message
         * @param    message    the string to be logged
         *
         */
        virtual void Trace(const std::string& tag, const std::string& message) const = 0;
    };
} //namespace


#endif /* ADOBEMOBILE_PLATFORMSHIM_LOGGINGSERVICEINTERFACE_H */
