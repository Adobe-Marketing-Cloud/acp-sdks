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
 ****************************************************************************/

#ifndef ADOBEMOBILE_SHARED_VISITORIDAUTHENTICATIONSTATE_H
#define ADOBEMOBILE_SHARED_VISITORIDAUTHENTICATIONSTATE_H

#include <string>

namespace AdobeMarketingMobile {
    class ToStringOptions;

    /**
     * This class describes the possible values of the visitor id authentication state parameter
     */
    enum class VisitorIdAuthenticationState : int32_t {
        UNKNOWN = 0,
        AUTHENTICATED,
        LOGGED_OUT
    };

    /**
     * Converts an int to its respective authentication state enum representation.
     *
     * If not match is found, returns VisitorIdAuthenticationState::UNKNOWN
     */
    VisitorIdAuthenticationState IntegerToVisitorIdAuthenticationState(const int32_t authentication_state);

    /**
     * Returns the authentication state string value for a given VisitorIdAuthenticationState.
     */
    std::string AuthenticationStateToString(const VisitorIdAuthenticationState value);

    /**
     * String version of the VisitorIdAuthenticationState used for logging
     */
    void ToStringImpl(std::ostream& the_stream,
                      const VisitorIdAuthenticationState value,
                      const ToStringOptions& options);
}

#endif /* ADOBEMOBILE_SHARED_VISITORIDAUTHENTICATIONSTATE_H */
