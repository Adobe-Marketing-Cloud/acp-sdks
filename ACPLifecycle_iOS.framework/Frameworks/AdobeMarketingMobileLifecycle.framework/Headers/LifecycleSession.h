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

#ifndef ADOBEMOBILE_LIFECYCLE_LIFECYCLESESSION_H
#define ADOBEMOBILE_LIFECYCLE_LIFECYCLESESSION_H
#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

#include <map>
#include <string>
#include <chrono>

namespace AdobeMarketingMobile {
    class DataStoreInterface;
    class SessionInfo;

    /**
     * Class for managing lifecycle sessions
     * Persists start, pause, and end timestamps for lifecycle sessions.
     * Also generates session context data for Analytics reporting
     */
    class LifecycleSession : public Object {
    public:

        explicit LifecycleSession(const std::shared_ptr<DataStoreInterface>& data_store);

        /**
         * Start a new lifecycle session.
         * Returns a SessionInfo object containing the previous session's data if it is a new session
         * Returns null if the previous session is resumed, or if lifecycle has already run
         *
         * @param start_timestamp_seconds long session start time
         * @param session_timeout_seconds int sessionTimeoutSeconds
         *
         * @return SessionInfo object containing previous session's data
         */
        std::shared_ptr<SessionInfo> Start(const std::chrono::seconds start_timestamp_seconds,
                                           const std::chrono::seconds session_timeout_seconds);

        /**
         * Pause current lifecycle session
         *
         * @param pause_timestamp_seconds pause timestamp
         */
        void Pause(const std::chrono::seconds pause_timestamp_seconds);

        /**
         * Gets session length data (used for Analytics reporting)
         *
         * @param start_timestamp_seconds session start timestamp
         * @param session_timeout_seconds session timeout
         * @param previous_session_info  SessionInfo object containing previous session's data
         *
         * @return map with session length context data
         */
        std::map<std::string, std::string> GetSessionData(const std::chrono::seconds start_timestamp_seconds,
                const std::chrono::seconds session_timeout_seconds,
                const std::shared_ptr<SessionInfo>& previous_session_info) const;

    private:
        std::shared_ptr<DataStoreInterface> data_store_;
        bool lifecycle_has_run_;
        const std::string LOG_TAG = "LifecycleSession";
    };

    /**
     * Container for lifecycle session information
     */
    class SessionInfo : public Object {
    public:
        explicit SessionInfo(const std::chrono::seconds start_timestamp,
                             const std::chrono::seconds pause_timestamp,
                             const bool is_crash);

        const std::chrono::seconds GetStartTimestamp() const;

        const std::chrono::seconds GetPauseTimestamp() const;

        const bool IsCrash() const;

    private:
        std::chrono::seconds pause_timestamp_seconds_;
        std::chrono::seconds start_timestamp_seconds_;
        bool is_crash_;
    };
}

#endif /* ADOBEMOBILE_LIFECYCLE_LIFECYCLESESSION_H */
