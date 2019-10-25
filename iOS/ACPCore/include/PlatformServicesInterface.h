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

#ifndef ADOBEMOBILE_PLATFORMSHIM_PLATFORMSERVICESINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_PLATFORMSERVICESINTERFACE_H

#include <chrono>
#include <memory>
#include "ObjectInterface.h"
#include "Expected.h"

namespace AdobeMarketingMobile {

    class LoggingServiceInterface;
    class NetworkServiceInterface;
    class DatabaseServiceInterface;
    class SystemInfoServiceInterface;
    class UIServiceInterface;
    class JsonUtilityServiceInterface;
    class FileSystemServiceInterface;
    class LocalStorageServiceInterface;
    class RemoteFileManagerServiceInterface;
    class CryptoServiceInterface;
    class EncodingServiceInterface;
    class URLServiceInterface;
    class CompressedFileServiceInterface;
    class ThreadingServiceInterface;

    /**
     * This is part of what defines the SDK's platform agnostic interface APIs to the native language services
     **/
    class PlatformServicesInterface : public virtual ObjectInterface {
    public:
        /**
         * Frees resources used by this, waiting up to `max_wait_duration` for the operation to complete.
         *
         * Calling Dispose() triggers clean up to occur asynchronously.
         *
         * After triggering the asynchronous disposal, this call will block for up to `max_wait_duration` for the
         * operation to complete.
         *
         * @param max_wait_duration - the maximum duration to block this call while waiting for cleanup to complete.
         *                            A `0` time indicates that we will return immediately.
         *
         * @return true if this was fully disposed
         */
        virtual bool Dispose(std::chrono::milliseconds max_wait_duration) = 0;

        /**
         * Returns the Logging service implementation from the Platform.
         *
         * @return LoggingService implementation, if the platform provides any. null otherwise.
         *
         * @see LoggingService
         */
        virtual std::shared_ptr<LoggingServiceInterface> GetLoggingService() const = 0;

        /**
         * Returns the Network service implementation from the Platform.
         *
         * @return NetworkService implementation, if the platform provides any. null otherwise.
         *
         * @see NetworkService
         */
        virtual std::shared_ptr<NetworkServiceInterface> GetNetworkService() const = 0;

        /**
         * Returns the Local Storage Service implementation from the Platform.
         *
         * @return LocalStorageService implementation, if the platform provides any. null otherwise.
         *
         * @see LocalStorageService
         */
        virtual std::shared_ptr<LocalStorageServiceInterface> GetLocalStorageService() const = 0;

        /**
         * Returns the Structured Data Service implementation from the Platform.
         *
         * @return DatabaseService implementation, if the platform provides any. null otherwise.
         *
         * @see DatabaseService
         */
        virtual std::shared_ptr<DatabaseServiceInterface> GetDatabaseService() const = 0;

        /**
         * Returns the System Information service implementation from the Platform.
         *
         * @return SystemInfoService implementation, if the platform provides any. null otherwise.
         *
         * @see SystemInfoService
         */
        virtual std::shared_ptr<SystemInfoServiceInterface> GetSystemInfoService() const = 0;

        /**
         * Returns the UI Service implementation from the Platform.
         *
         * @return UIService implementation, if the platform provides any. null otherwise.
         *
         * @see UIService
         */
        virtual std::shared_ptr<UIServiceInterface> GetUIService() const = 0;

        /**
         * Returns the Json Utility service implementation from the Platform.
         *
         * @return JsonUtilityService implementation, if the platform provides any. null otherwise.
         *
         * @see JsonUtilityService
         */
        virtual std::shared_ptr<JsonUtilityServiceInterface> GetJsonUtilityService() const = 0;

        /**
         * Returns the File System service from the Platform. The File System Service contains
         * utility methods for dealing with directory manipulations.
         *
         * @return FileSystemService implementation if the platform provides any. Null otherwise.
         * @see FileSystemService
         */
        virtual std::shared_ptr<FileSystemServiceInterface> GetFileSystemService() const = 0;

        /**
         * Returns the Remote File Manager service from the Platform.
         * The Remote File Manager Service replace the old RemoteDownloader+CacheManager functionality/
         *
         * @return ptr to RemoteFileManagerServiceInterface or SdkError
         * @see RemoteFileManagerService
         */
        virtual Expected<std::shared_ptr<RemoteFileManagerServiceInterface>> GetRemoteFileManagerService() const = 0;

        /**
         * Returns the Crypto Service service implementation from the Platform.
         *
         * @return CryptoService implementation, if the platform provides any. null otherwise.
         *
         * @see CryptoService
         */
        virtual std::shared_ptr<CryptoServiceInterface> GetCryptoService() const = 0;

        /**
         * Returns the Encoding Service implementation from the Platform.
         *
         * @return EncodingService implementation, if the platform provides any. null otherwise.
         *
         * @see EncodingService
         */
        virtual std::shared_ptr<EncodingServiceInterface> GetEncodingService() const = 0;

        /**
         * Returns the URL Service implementation from the Platform.
         *
         * @return URL implementation, if the platform provides any. null otherwise.
         *
         * @see URLService
         */
        virtual std::shared_ptr<URLServiceInterface> GetURLService() const = 0;

        /**
         * Returns the CompressedFileService implementation from the Platform.
         *
         * @return CompressedFileService implementation, if the platform provides any. null otherwise.
         *
         * @see CompressedFileService
         */
        virtual std::shared_ptr<CompressedFileServiceInterface> GetCompressedFileService() const = 0;

        virtual std::shared_ptr<ThreadingServiceInterface> GetThreadingService() const;

    };

    namespace ErrorCodes {
        constexpr static const char* MISSING_PLATFORM_SERVICES =
                    "platform_services.missing_service"; ///< A missing platform service exception

    }

} //namespace


#endif /* ADOBEMOBILE_PLATFORMSHIM_PLATFORMSERVICESINTERFACE_H */
