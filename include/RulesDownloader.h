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

#ifndef ADOBEMOBILE_RULESENGINE_RULESDOWNLOADER_H
#define ADOBEMOBILE_RULESENGINE_RULESDOWNLOADER_H

#include <string>
#include "Common.h"
#include "Object.h"

namespace AdobeMarketingMobile {
    class RemoteFileManagerServiceInterface;
    class CryptoServiceInterface;
    class FileSystemServiceInterface;
    class CompressedFileServiceInterface;
    class ZipBundleHandler;

    class RulesDownloader : public Object {
    public:

        /**
         * Create RulesDownloader for the given URL.
         *
         * @param platform_services an instance of PlatformServicesInterface
         * @param cache_folder a string containing the subfolder to use for caching of downloaded urls
         * @param bundle_ready_callback a callback function to be called when the download is completed
         * @throws ErrorCodes::MISSING_PLATFORM_SERVICES if the RemoteFileManagerService is not available.
         */
        explicit RulesDownloader(const std::shared_ptr<PlatformServicesInterface>& platform_services,
                                 const std::string& cache_folder,
                                 const std::function<void(const std::string&, const std::string&)>& bundle_ready_callback);

        /**
         * Start asynchronous download of rules. Once finished, triggers completed callback function
         * passing URI to local cached file.
         *
         * @param url the remote url to download the rule configuration
         */
        ADOBE_VIRTUAL_FOR_TESTS
        void StartDownload(const std::string& url);

        /**
         * Processes the downloaded file and returns the destination path
         *
         * @param downloaded_file_path The file that was downloaded by this
         * @return The destination path where the processed file contents were stored,
         *          null if the processing failed
         */
        std::string ProcessBundle(const std::string& downloaded_file_path);

    private:
        /**
         * @private
         * Called when rules have been downloaded from the server and the content url is passed in
         *
         * @param file_path The path to the downloaded rules zip file
         */
        void OnDownloadComplete(const std::string& file_path);

        void RulesBundleDownloaded(const std::string& bundlePath, const std::string& url);

        std::shared_ptr<RemoteFileManagerServiceInterface> manager_;
        std::shared_ptr<FileSystemServiceInterface> file_system_service_;
        std::shared_ptr<CryptoServiceInterface> crypto_service_;
        std::shared_ptr<ZipBundleHandler> zip_bundle_handler_;
        std::function<void(const std::string&, const std::string&)> bundle_ready_callback_;
        std::string url_;
        std::string cache_folder_;
    };
}

#endif /* ADOBEMOBILE_RULESENGINE_RULESDOWNLOADER_H */
