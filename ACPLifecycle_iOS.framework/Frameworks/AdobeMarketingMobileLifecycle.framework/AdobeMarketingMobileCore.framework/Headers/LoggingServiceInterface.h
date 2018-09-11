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
    };
} //namespace


#endif /* ADOBEMOBILE_PLATFORMSHIM_LOGGINGSERVICEINTERFACE_H */
