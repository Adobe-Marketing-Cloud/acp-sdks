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

#ifndef ADOBEMOBILE_LIFECYCLE_LIFECYCLEMETRICSBUILDER_H
#define ADOBEMOBILE_LIFECYCLE_LIFECYCLEMETRICSBUILDER_H

#include <chrono>
#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>


namespace AdobeMarketingMobile {
    /**
     * @class LifecycleMetricsBuilder
     *
     * The responsibility of LifecycleMetricsBuilder is to build an EventData object that contains the
     * various pieces of lifecycle data. This builder has the ability to add all install, launch, and
     * upgrade data to the EventData object to be built and returned.
     */

    class LifecycleMetricsBuilder {
    public:
        /**
         * Create a new instance of a LifecycleMetricsBuilder Module.
         *
         * @param platform_services platform services interface to get access to System Info and Local Storage
         * @param timestamp timestamp of event to be used in all calculations
         */
        explicit LifecycleMetricsBuilder(const std::shared_ptr<PlatformServicesInterface>& platform_services,
                                         std::chrono::seconds timestamp);

        LifecycleMetricsBuilder(const LifecycleMetricsBuilder&) = delete;
        LifecycleMetricsBuilder& operator=(const LifecycleMetricsBuilder&) = delete;
        LifecycleMetricsBuilder(LifecycleMetricsBuilder&&) = delete;
        LifecycleMetricsBuilder&& operator=(LifecycleMetricsBuilder&&) = delete;

        /**
         * Adds all install data key value pairs to lifecycle_event_data_
         *
         * @return pointer to the builder
         */
        ADOBE_VIRTUAL_FOR_TESTS LifecycleMetricsBuilder& AddInstallData();

        /**
         * Adds all launch data key value pairs to lifecycle_event_data_
         *
         * @return pointer to the builder
         */
        ADOBE_VIRTUAL_FOR_TESTS LifecycleMetricsBuilder& AddLaunchData();

        /**
         * Adds all generic data key value pairs to the lifecycle data map (e.g. day of week, hour of day, no of launches)
         * This method also increments the no of launches, make sure that this method is called only once, when lifecycle start is called
         *
         * @return pointer to the builder
         */
        ADOBE_VIRTUAL_FOR_TESTS LifecycleMetricsBuilder& AddGenericData();

        /**
         * Adds crash info to the lifecycle data map if previous_session_crash is true
         *
         * @param previous_session_crash specifies if there was a crash in the previous session
         * @return pointer to the builder
         */
        ADOBE_VIRTUAL_FOR_TESTS LifecycleMetricsBuilder& AddCrashData(const bool previous_session_crash);

        /**
         * Adds all upgrade data key value pairs to lifecycle_event_data_
         *
         * @param upgrade boolean specifying if this was an upgrade or not
         * @return pointer to the builder
         */
        ADOBE_VIRTUAL_FOR_TESTS LifecycleMetricsBuilder& AddUpgradeData(const bool upgrade);

        /**
         * Adds all core data key value pairs to lifecycle_event_data_
         *
         * @return pointer to the builder
         */
        ADOBE_VIRTUAL_FOR_TESTS LifecycleMetricsBuilder& AddCoreData();

        /**
         * Returns the context data map that was built
         *
         * @return the context data map that was built
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::string> Build() const;

    private:
        /**
         * @private
         * Creates a readable string from timestamp in format of m/d/yyy
         *
         * @param timestamp current timestamp for lifecycle calculations
         * @return Formatted date
         */
        std::string StringFromTimestamp(std::chrono::seconds timestamp);

        /**
         * @private
         * Converts a std::chrono::seconds to the type tm
         *
         * @param timestamp current timestamp for lifecycle calculations
         * @return tm of the timestamp provided
         */
        std::tm ConvertToTM(std::chrono::seconds timestamp);

        /**
         * @private
         * Calculates the number of days between two times provided
         *
         * @param start the starting
         * @param end the end date
         * @return tm of the timestamp provided
         */
        int32_t CalculateDaysBetween(std::tm& start, std::tm& end);

        /**
         * @private
         * Generates the Application ID string from Application name and versions
         *
         * @param system_info_service shared pointer to SystemInfoServiceInterface for app info
         * @return string representation of the Application ID
         */
        std::string GetApplicationId(const std::shared_ptr<SystemInfoServiceInterface>& system_info_service);

        /**
         * @private
         * Generates the Operating System string from OS name and Version
         *
         * @param system_info_service shared pointer to SystemInfoServiceInterface for os info
         * @return string representation of the Operating System
         */
        std::string GetOperatingSystem(const std::shared_ptr<SystemInfoServiceInterface>& system_info_service);

        /**
         * @private
         * Generates the resolution string from DisplayInformationInterface
         *
         * @param system_info_service shared pointer to SystemInfoServiceInterface for device info
         * @return string representation of the resolution
         */
        std::string GetResolution(const std::shared_ptr<SystemInfoServiceInterface>& system_info_service);

        /**
         * @private
         * Retreives the active locale from system info service and replaces '_' with '-'
         *
         * @param system_info_service shared pointer to SystemInfoServiceInterface for device info
         * @return string representation of the locale
         */
        std::string GetLocale(const std::shared_ptr<SystemInfoServiceInterface>& system_info_service);

        /**
         * @private
         * Platform Services Interface, passed into constructor.
         * Allowed to be nullptr. Must check for nullptr before using!
         */
        std::shared_ptr<PlatformServicesInterface> platform_services_;

        /**
         * @private
         * Timestamp of the original event
         */
        std::chrono::seconds timestamp_;

        /**
         * @private
         * Pointer to Lifecycle's data store
         */
        std::shared_ptr<DataStoreInterface> lifecycle_data_store_;

        /**
         * @private
         * Map containing the lifecycle context data being built
         */
        std::map<std::string, std::string> lifecycle_data_;
    };
}
#endif /* ADOBEMOBILE_LIFECYCLE_LIFECYCLEMETRICSBUILDER_H */
