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

#ifndef ADOBEMOBILE_RULESENGINE_RULESBUNDLENETWORKPROTOCOLHANDLER_H
#define ADOBEMOBILE_RULESENGINE_RULESBUNDLENETWORKPROTOCOLHANDLER_H

#include <chrono>
#include "Object.h"

namespace AdobeMarketingMobile {

    /**
     * This is the contract for a concrete implementation that would support
     * processing a Rules Engine bundle downloaded from the configured end-point
     *
     * The interface allows the handling of the actual file type downloaded to be changed / plugged -in/out.
     * The implementation is responsible for processing the downloaded bundle (file)
     */
    class RulesBundleNetworkProtocolHandler : virtual ObjectInterface {

        /**
         * Process the file that was downloaded by the RulesDownloader.
         *
         * The implementation is free to process the file as it wishes. The processed contents should be stored in the
         * #output_path path.
         *
         * @param downloaded_bundle The file that was downloaded by the RulesDownloader
         * @param output_path The absolute path of the output folder. The implementation is free to create sub-folders underneath.
         *
         * @return Indication of whether the processing was successful
         */
        virtual bool ProcessDownloadedBundle(const std::string& downloaded_bundle,
                                             const std::string& output_path) = 0;
    };
}

#endif /* ADOBEMOBILE_RULESENGINE_RULESBUNDLENETWORKPROTOCOLHANDLER_H */



