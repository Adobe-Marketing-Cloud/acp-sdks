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



