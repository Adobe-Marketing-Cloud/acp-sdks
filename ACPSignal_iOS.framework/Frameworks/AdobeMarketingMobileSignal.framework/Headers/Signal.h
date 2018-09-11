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


#ifndef ADOBEMOBILE_SIGNAL_SIGNAL_H
#define ADOBEMOBILE_SIGNAL_SIGNAL_H

#include <AdobeMarketingMobileCore/Common.h>
#include <AdobeMarketingMobileCore/InternalModule.h>

namespace AdobeMarketingMobile {
    class Event;
    enum class MobilePrivacyStatus : int32_t;
    class Variant;
    class UIServiceInterface;
    class URLServiceInterface;
    class SignalHitsDatabase;

    /**
     * @class Signal
     *
     * Module that implements postback functionality in the SDK.
     */
    class Signal : public InternalModule {
        // TODO: (AMSDK-5882) Migrate to SignalMethods pattern
        friend class TestableSignal; // for testing

    public:
        static const std::string LOG_PREFIX; ///< The log prefix for this module

        /**
         * Create a new instance of the signal module.
         */
        Signal();

        // ================================================
        // public methods
        // ================================================
        /**
         * Asynchronously updates the privacy status to the given value.
         *
         * @param  privacy_status the new privacy status
         *
         */
        ADOBE_VIRTUAL_FOR_TESTS void UpdatePrivacyStatus(const MobilePrivacyStatus privacy_status);

        /**
         * Queues the given signal event triggered by Rules Engine for asynchronous processing.
         *
         * @param event the signal event containing the consequence data
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleSignalConsequenceEvent(const std::shared_ptr<Event>& event);

        /**
         * Reads the URL value from the rules consequence detail map and passes it to the {@code UIService} to open.
         *
         * @param consequence_detail map containing the URL to be openned
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleOpenUrlConsequence(const std::map<std::string, std::shared_ptr<Variant>>&
                consequence_detail);

    protected:

        // ================================================
        // protected methods
        // ================================================

        /**
         * @see Module::OnRegistered()
         */
        void OnRegistered() override;

        /**
         * @see Module::OnUnregistered()
         */
        void OnUnregistered() override;

        /**
         * Creates the database instance.
         *
         * Present to allow mocks to be substituted during testing.
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<SignalHitsDatabase> CreateDatabase();

    private:

        // ================================================
        // private methods
        // ================================================

        /**
         * @private
         *
         * Process pending signal events. Should only be invoked from task thread.
         */
        ADOBE_VIRTUAL_FOR_TESTS void TryProcessQueuedEvent();

        /**
         * @private
         * Check if configuration shared state is ready, if so go ahead and process the signal event,
         * otherwise just return false.
         * <p>
         * Should only be invoked from task thread.
         *
         * @param event the signal event
         * @return {@code bool} representing the status of the event processing
         */
        ADOBE_VIRTUAL_FOR_TESTS bool ProcessSignalEvent (const std::shared_ptr<Event>& event);

        /**
         * @see Module::GetSharedStateName()
         **/
        std::string GetSharedStateName() override;

        /**
         * Retrieves the UIServiceInterface from platform services. It may return nullptr if the platform services or
         * the UIServiceInterface are not initialized.
         */
        std::shared_ptr<UIServiceInterface> GetUIService();

        /**
         * Retrieves the URLServiceInterface from platform services. It may return nullptr if the platform services or
         * the URLServiceInterface are not initialized.
         */
        std::shared_ptr<URLServiceInterface> GetURLService();


        // ================================================
        // private members
        // ================================================

        /**
         * @private
         * Signal database used for queuing the signal template hits
         */
        std::shared_ptr<SignalHitsDatabase> signal_hits_database_;


        // TODO: (AMSDK-5883) unprocessed_events_ is not being synchronized properly
        /**
         * @private
         * Queue of signal events to be processed (in fifo order).
         */
        std::deque<std::shared_ptr<Event>> unprocessed_events_;
    };
}

#endif /* ADOBEMOBILE_SIGNAL_SIGNAL_H */
