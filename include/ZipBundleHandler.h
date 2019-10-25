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
