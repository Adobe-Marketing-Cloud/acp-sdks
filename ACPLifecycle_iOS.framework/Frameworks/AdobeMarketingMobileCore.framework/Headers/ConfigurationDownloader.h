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
