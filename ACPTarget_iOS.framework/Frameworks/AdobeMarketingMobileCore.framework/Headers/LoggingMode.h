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

#ifndef ADOBEMOBILE_PLATFORMSHIM_LOGGINGMODE_H
#define ADOBEMOBILE_PLATFORMSHIM_LOGGINGMODE_H

namespace AdobeMarketingMobile {

    enum class LoggingMode : int32_t {
        ERROR_LOG = 0,
        WARNING_LOG = 1,
        DEBUG_LOG = 2,
        VERBOSE_LOG = 3,

    };
} //namespace

#endif /* ADOBEMOBILE_PLATFORMSHIM_LOGGINGMODE_H */
