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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDOWNLOADER_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDOWNLOADER_H

#include <string>
#include "Object.h"

namespace AdobeMarketingMobile {
    class NetworkServiceInterface;
    class RemoteFileManagerServiceInterface;
    class SystemInfoServiceInterface;

    class ConfigurationDownloader : public Object {
    public:
        ConfigurationDownloader(const std::shared_ptr<RemoteFileManagerServiceInterface>& remote_file_service,
                                const std::string& url);

        virtual std::string DownloadConfig();

        virtual std::string LoadCachedConfig();

        const std::string GetUrl() const;

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;

    private:
        const std::string url_;
        std::shared_ptr<RemoteFileManagerServiceInterface> manager_;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDOWNLOADER_H */
