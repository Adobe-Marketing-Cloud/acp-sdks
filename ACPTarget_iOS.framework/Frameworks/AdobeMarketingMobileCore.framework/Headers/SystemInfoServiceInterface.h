/* ************************************************************************
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

#ifndef ADOBEMOBILE_PLATFORMSHIM_SYSTEMINFOSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_SYSTEMINFOSERVICEINTERFACE_H

#include <memory>
#include <string>
#include <locale>
#include <fstream>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {

    class DisplayInformationInterface : public virtual ObjectInterface {
    public:
        /**
         * Returns absolute width of the available display size in pixels.
         *
         * @return width in pixels if available. -1 otherwise.
         */
        virtual int32_t GetWidthPixels() const = 0;

        /**
         * Returns absolute height of the available display size in pixels.
         *
         * @return height in pixels if available. -1 otherwise.
         */
        virtual int32_t GetHeightPixels() const = 0;

        /**
         * Returns the screen dots-per-inch
         *
         * @return dpi if available. -1 otherwise.
         */
        virtual int32_t GetDensityDpi() const = 0;

    };

    class SystemInfoServiceInterface : public virtual ObjectInterface {
    public:
        enum class ConnectionStatus : int32_t {
            CONNECTED = 0,
            DISCONNECTED,
            UNKNOWN
        };

        static constexpr const uint32_t MAX_THREAD_NAME_LEN{15};

        /**
         * Returns the currently selected / active locale value (as set by the user on the system).
         *
         * @return Locale value.
         */
        virtual std::locale GetActiveLocale() const = 0;

        /**
         * Returns the directory which can be used as a application data directory.
         *
         * @return A directory path string representing the application data directory
         */
        virtual std::string GetApplicationBaseDir() const = 0;

        /**
         * Returns the application specific cache directory. The application will be able to read and write to the
         * directory, but there is no guarantee made as to the persistence of the data (it may be deleted by the system
         * when storage is required).
         *
         * @return A directory path string representing the application cache directory.
         */
        virtual std::string GetApplicationCacheDir() const = 0;

        /**x
         * Returns the application name.
         *
         * @return Application name or empty if not available.
         */
        virtual std::string GetApplicationName() const = 0;

        /**
         * Returns the application version.
         *
         * @return Application version or empty if not available.
         */
        virtual std::string GetApplicationVersion() const = 0;

        /**
         * Returns the application version code as a string.
         *
         * @return Application version code formatted as string using the active locale, or empty if not available.
         */
        virtual std::string GetApplicationVersionCode() const = 0;

        /**
         * Return the contents of the asset file as a string. The given filename is a relative path to the
         * application's assets folder. The application must have read access to the assets folder.
         *
         * @param filename relative file path of a file within the application's assets folder
         * @return string contents of the assets file, or an empty string in case of an error
         */
        virtual std::string GetAsset(const std::string& filename) const = 0;

        /**
         * Returns a string that identifies a particular device OS build.
         *
         * @return Build ID string.
         */
        virtual std::string GetDeviceBuildId() const = 0;

        /**
         * Returns a human readable device name.
         *
         * @return Device name or empty if not available.
         */
        virtual std::string GetDeviceName() const = 0;

        /**
         * Returns information about the display hardware, as returned by the underlying OS.
         *
         * @see DisplayInformation
         *
         * @return std::shared_ptr<DisplayInformation> Display information, or null if not available
         */
        virtual std::shared_ptr<DisplayInformationInterface> GetDisplayInformation() const = 0;

        /**
         * Returns a human readable mobile carrier name.
         *
         * @return A std::string representing the carrier name or empty if not available.
         */
        virtual std::string GetMobileCarrierName() const = 0;

        /**
         * Returns the state of the network connectivity
         *
         * @return SystemInfoService::ConnectionStatus.
         */
        virtual SystemInfoServiceInterface::ConnectionStatus GetNetworkConnectionStatus() const = 0;

        /**
         * Returns the string representation of the operating system name.
         *
         * @return Operating system name or empty if not available.
         */
        virtual std::string GetOperatingSystemName() const = 0;

        /**
         * Returns the string representation of the canonical platform name.
         *
         * @return Platform name string.
         */
        virtual std::string GetCanonicalPlatformName() const = 0;

        /**
         * @return a string with the current line number
         *
         * implementation is platform specific.
         */
        virtual std::string GetCurrentStackTrace() const = 0;

        /**
         * Returns the string representation of the operating system version.
         *
         * @return Operating system version or empty if not available.
         */
        virtual std::string GetOperatingSystemVersion() const = 0;

        /**
         * Returns the property value specific to the key from the manifest file.
         *
         * @param resource_key std::string key in the manifest file.
         * @return A std::string value of the requested property or empty if not available.
         */
        virtual std::string GetProperty(const std::string& resource_key) const = 0;

        /**
         * Returns a string that identifies the SDK running mode, e.g. Application, Extension
         *
         * @return Running mode string
         */
        virtual std::string GetRunMode() const = 0;

        /**
         * Returns the version for the SDK, which is determined by the platform
         *
         * @return string containing the SDK version
         */
        virtual std::string GetSdkVersion() const = 0;

        /**
         * Returns the default platform/device user agent string
         *
         * @return string containing the default user agent
         */
        virtual std::string GetDefaultUserAgent() const = 0;

        /**
         * Set the name of the current thread
         *
         * @param name - Empty names are ignored and names longer than MAX_THREAD_NAME_LEN chars are truncated.
         */
        virtual void SetCurrentThreadName(const std::string& name) const = 0;

        /**
         * Sets the current system info service. Intended for use by Core.
         */
        static void SetCurrentService(const std::shared_ptr<SystemInfoServiceInterface>& new_service);

        /**
         * @return the current system info service
         */
        static std::shared_ptr<SystemInfoServiceInterface> GetCurrentService();

    private:
        /**
         * @private
         * Lock for `current_service`
         */
        static std::mutex mutex;

        /**
         * @private
         * The current system info service.
         * Synchronized on mutex;
         */
        static std::shared_ptr<SystemInfoServiceInterface> current_service;
    };
}

#endif /* ADOBEMOBILE_PLATFORMSHIM_SYSTEMINFOSERVICEINTERFACE_H */
