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

#ifndef ADOBEMOBILE_RULESENGINE_ZIPBUNDLEHANDLER_H
#define ADOBEMOBILE_RULESENGINE_ZIPBUNDLEHANDLER_H

#include <string>
#include "RulesBundleNetworkProtocolHandler.h"

namespace AdobeMarketingMobile {
    class RulesFileMetadata;
    class CompressedFileServiceInterface;
    class FileSystemServiceInterface;

    class ZipBundleHandler : public Object, public virtual RulesBundleNetworkProtocolHandler {
    public:

        /**
         * ZipBundleHandler constructor
         * The FileSystemService and CompressedFileService will be used for extracting the zip file
         * when ZipBundleHandler::ProcessDownloadedBundle is called.
         *
         * @see ZipBundleHandler::ProcessDownloadedBundle
         */
        ZipBundleHandler(const std::shared_ptr<FileSystemServiceInterface>& file_system_service,
                         const std::shared_ptr<CompressedFileServiceInterface>& compressed_file_service);

        /**
         * Extracts the downloaded bundle in the provided output path and removes the downloaded zip after extraction.
         *
         * @param downloaded_bundle the path to the downloaded zip file
         * @param output_path the path where the extracted zip content will be placed
         *
         * @see RulesBundleNetworkProtocolHandler:ProcessDownloadedBundle
         */
        bool ProcessDownloadedBundle(const std::string& downloaded_bundle,
                                     const std::string& output_path);
    private:
        std::shared_ptr<FileSystemServiceInterface> file_system_service_;
        std::shared_ptr<CompressedFileServiceInterface> compressed_file_service_;
    };
}

#endif /* ADOBEMOBILE_RULESENGINE_ZIPBUNDLEHANDLER_H */
