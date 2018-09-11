/* ************************************************************************
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

#ifndef ADOBEMOBILE_PLATFORMSHIM_REMOTEFILEMANAGERSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_REMOTEFILEMANAGERSERVICEINTERFACE_H

#include <string>
#include <deque>
#include "ObjectInterface.h"
#include "Expected.h"

namespace AdobeMarketingMobile {

    /* forward declaration */
    class NetworkServiceInterface;

    /*
     * Errors specific to the RemoteFileManagerService Interface
     */
    namespace ErrorCodes {
        // Platform shim errors
        constexpr static const char* REMOTEFILEMANAGER_SERVICES_FAILURE{"remotefilemanager.services_failed"}; ///< One or more of the required services are not available.
        constexpr static const char* REMOTEFILEMANAGER_REQUEST_FAILURE{"remotefilemanager.request_failed"}; ///< Network failure when requesting file. Response code available.
        constexpr static const char* REMOTEFILEMANAGER_CACHE_FAILURE{"remotefilemanager.cache_failed"}; ///< File system failure when requesting file. File system error available.
    }

    /*
     * Helper class for returning remote file contents.
     */
    class RemoteFileInterface : public virtual ObjectInterface {
    public:

        /**
         * Get local path to cached copy of remote file as a URI.
         * This must be accessible to the HTML renderer we are using (e.g. for Messages).
         *
         * @return path to local cached file
         */
        virtual std::string ToUri() = 0;

        /**
         * Get the contents of the remote file as a JSON string.
         *
         * @return JSON data
         */
        virtual std::string ReadJsonStringFromFile() = 0;
    };


    /*
     * This interface is intended to replace the current usage of RemoteDownloader and CacheManager.
     * This higher level interface will be more flexible when porting cross-platform.
     *
     * Current usage patterns:
     *  1. RemoteDownloader --> startDownload --> getFileForCachedURL --> onDownloadComplete --> readFromFile (and then convert to JSON)
     *  2. RemoteDownloader --> startDownloadSync --> getFileForCachedURL --> readJSONFromFile
     *  3. CacheManager --> getFileForCachedURL --> readJSONFromFile
     *  4. CacheManager --> getFileForCachedURL --> getURL --> downloadAssetCollection --> HTML Renderer
     *  5. RemoteDownloaded --> syncRemoteAssets --> deleteCachedUrlsNotInList
     *
     * You may encounter the following errors:
     *  HTTP response errors (e.g. something besides HTTP/200 OK)
     *  OS networking errors (e.g. network timeout)
     *  OS filesystem errors (e.g. someone deleted the cached file out from under us)
     *
     */
    class RemoteFileManagerServiceInterface : public virtual ObjectInterface {
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
         * Asynchronously get the file corresponding to the url passed.
         * If file was cached and we could not get an updated file, return the cached file.
         * If file was NOT cached and we could not get the file, return an error.
         * WARNING! The file may be returned on a different thread than the calling thread.
         *
         * @param cache_subfolder - Sub-folder that remote file should be cached in. Use empty string for root folder.
         * @param url - the remote file url. Schemes supported: https, http(?)
         * @param completed - callback function called when download has completed or failed
         */
        virtual void GetFileAsync(const std::string& cache_subfolder,
                                  const std::string& url,
                                  const std::function<void(const Expected<std::shared_ptr<RemoteFileInterface>>&)>& completed) = 0;

        /**
         * Synchronously get the file corresponding to the url passed.
         * If file was cached and we could not get an updated file, return the cached file.
         * If file was NOT cached and we could not get the file, return an error.
         * WARNING! This call will block until the file is fully downloaded or errors out.
         *
         * @param cache_subfolder - Sub-folder that remote file should be cached in. Use empty string for root folder.
         * @param url - the url to look for the remote file at. Schemes supported: https, http(?)
         * @return ptr to RemoteFileInterface or SdkError
         */
        virtual Expected<std::shared_ptr<RemoteFileInterface>> GetFileSync(const std::string& cache_subfolder,
                const std::string& url) = 0;

        /**
         * Get a file from the cache using the url as the lookup key. Optionally ignore partially downloaded files.
         * If file was not cached, return an error.
         *
         * @param cache_subfolder - Sub-folder that remote file should be cached in. Use empty string for root folder.
         * @param url - the remote file url. Schemes supported: https, http(?)
         * @param ignore_partial_downloads - ignore files which are still being downloaded
         * @return ptr to RemoteFileInterface or SdkError
         */
        virtual Expected<std::shared_ptr<RemoteFileInterface>> GetFileFromCache(const std::string& cache_subfolder,
                const std::string& url,
                bool ignore_partial_downloads) = 0;

        /**
         * Delete all urls from the cache that are not found in the list passed.
         * If list is empty, all urls in the cache will be removed.
         * If none of the urls in the list are in the cache, all urls in the cache will be removed.
         *
         * @param cache_subfolder - Sub-folder that remote file should be cached in. Use empty string for root folder.
         * @param urls_to_retain - the remote file url. Schemes supported: https, http(?)
         */
        virtual void DeleteCachedDataNotInList(const std::string& cache_subfolder,
                                               const std::deque<std::string>& urls_to_retain) = 0;

    };

}

#endif /* ADOBEMOBILE_PLATFORMSHIM_REMOTEFILEMANAGERSERVICEINTERFACE_H */
