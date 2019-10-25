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
