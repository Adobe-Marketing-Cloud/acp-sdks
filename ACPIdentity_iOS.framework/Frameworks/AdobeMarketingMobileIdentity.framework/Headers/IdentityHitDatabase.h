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


#ifndef ADOBEMOBILE_IDENTITY_HIT_DATABASE_H
#define ADOBEMOBILE_IDENTITY_HIT_DATABASE_H

#include "Identity.h"

namespace AdobeMarketingMobile {
    class ConfigurationSharedStateIdentity;
    class Event;
    class FileSystemServiceInterface;
    class Identity;
    class IdentityDatabaseHit;
    class IdentityDatabaseHitSchema;
    class IdentityHitProcessor;
    class IdentityHitQueue;
    class PlatformServicesInterface;
    class SystemInfoServiceInterface;
    enum class MobilePrivacyStatus : int32_t;

    class IdentityHitDatabase: public Object {

    public:

        static std::shared_ptr<IdentityHitDatabase> CreateIdentityDatabase(const std::shared_ptr<Identity>& parent,
                const std::shared_ptr<PlatformServicesInterface>& services,
                const std::shared_ptr<IdentityHitQueue>& queue);

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
        ADOBE_VIRTUAL_FOR_TESTS bool Dispose(std::chrono::milliseconds max_wait_duration);

        virtual void Queue(const std::string& url,
                           const std::shared_ptr<ConfigurationSharedStateIdentity>& config,
                           const std::shared_ptr<Event>& event);

        /**
         * Updates the database based on the MobilePrivacyStatus.
         * When MobilePrivacyStatus::OPT_IN, resume processing hits.
         * When MobilePrivacyStatus::UNKNOWN, suspend processing hits.
         * When MobilePrivacyStatus::OPT_OUT, delete hits and suspend processing.
         *
         * @param privacy_status the new MobilePrivacyStatus
         */
        ADOBE_VIRTUAL_FOR_TESTS
        void UpdatePrivacyStatus(const MobilePrivacyStatus privacy_status);

    protected:
        IdentityHitDatabase();
    private:
        void Init(const std::shared_ptr<PlatformServicesInterface>& services);
        void ResetEventNumberAndPairIdForExistingRequests();

        std::shared_ptr<IdentityDatabaseHitSchema> identity_hit_schema_;
        std::shared_ptr<IdentityHitQueue> hit_queue_;
        std::shared_ptr<IdentityHitProcessor> hit_processor_;
        std::shared_ptr<SystemInfoServiceInterface> system_info_service_;
        std::shared_ptr<FileSystemServiceInterface> file_system_service_;
    };
}



#endif /* ADOBEMOBILE_IDENTITY_HIT_DATABASE_H */
