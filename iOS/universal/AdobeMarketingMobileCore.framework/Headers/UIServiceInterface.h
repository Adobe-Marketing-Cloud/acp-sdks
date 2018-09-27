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

#ifndef ADOBEMOBILE_PLATFORMSHIM_UISERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_UISERVICEINTERFACE_H

#include <chrono>
#include "Object.h"
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    /**
     * Enum representing application states
     */
    enum class AppState : int32_t {
        FOREGROUND = 0, // app is in the foreground
        BACKGROUND,     // app is in the background
        UNKNOWN         // unknown app state
    };

    /**
     * Alert message event listener
     */
    class AlertListenerInterface : public virtual ObjectInterface {
    public:
        /**
         * Invoked on positive button clicks
         */
        virtual void OnPositiveResponse() = 0;

        /**
         * Invoked on negative button clicks
         */
        virtual void OnNegativeResponse() = 0;

        /**
         * Invoked when the alert is displayed
         */
        virtual void OnShow() = 0;

        /**
         * Invoked when the alert is dismissed
         */
        virtual void OnDismiss() = 0;
    };

    /**
     * UI service interface defining a fullscreen message
     */
    class FullScreenMessageUiInterface : public virtual ObjectInterface {
    public:
        /**
         * Display the fullscreen message
         */
        virtual void Show() = 0;

        /**
         * Open a url from this message
         *
         * @param url String the url to open
         */
        virtual void OpenUrl(const std::string& url) = 0;

        /**
         * Remove the fullscreen message from view.
         */
        virtual void Remove() = 0;
    };

    /**
     * Fullscreen message event listener
     */
    class FullscreenListenerInterface : public virtual ObjectInterface {
    public:
        /**
         * Invoked when the fullscreen message is displayed
         *
         * @param message FullscreenMessage the message being displayed
         */
        virtual void OnShow(const std::shared_ptr<FullScreenMessageUiInterface>& message) = 0;

        /**
         * Invoked when the fullscreen message is dismissed
         *
         * @param message FullscreenMessage the message being dismissed
         */
        virtual void OnDismiss(const std::shared_ptr<FullScreenMessageUiInterface>& message) = 0;

        /**
         * Invoked when the fullscreen message is attempting to load a url
         *
         * @param message FullscreenMessage the message attempting to load the url
         * @param url     String the url being loaded by the message
         *
         * @return True if the core wants to handle the URL (and not the fullscreen message view implementation)
         */
        virtual bool OverrideUrlLoad(const std::shared_ptr<FullScreenMessageUiInterface>& message, const std::string& url) = 0;
    };

    /**
     * Listener for app state transition events
     */
    class AppStateListenerInterface : public virtual ObjectInterface {
    public:
        /**
         * invoked when the application transitions into the AppState::FOREGROUND state
         */
        virtual void OnForeground() = 0;

        /**
         * invoked when the application transitions into the AppState::BACKGROUND state
         */
        virtual void OnBackground() = 0;
    };

    /**
     * Listener for UI floating button
     */
    class FloatingButtonListenerInterface : public virtual ObjectInterface {
    public:
        /**
         * Invoked when the floating button is tapped
         */
        virtual void OnTapDetected() = 0;

        /**
         * Invoked when the floating button is dragged on the screen
         */
        virtual void OnPanDetected() = 0;
    };

    /**
     * UI service interface defining a floating button
     */
    class FloatingButtonInterface : public virtual ObjectInterface {
    public:
        /**
         * Display the floating button on the screen
         */
        virtual void Display() = 0;

        /**
         * Remove the floating button
         */
        virtual void Remove() = 0;
    };

    /**
     * Interface for displaying alerts, local notifications, and fullscreen web views
     */
    class UIServiceInterface : public virtual ObjectInterface {
    public:

        /**
         * Display an alert
         *
         * @param title              String alert title
         * @param message            String alert message
         * @param positive_button_text String positive response button text. Positive button will not be displayed if this value is null or empty
         * @param negative_button_text String negative response button text. Negative button will not be displayed if this value is null or empty
         * @param listener      AlertListener listener for alert message events
         */
        virtual void ShowAlert(const std::string& title,
                               const std::string& message,
                               const std::string& positive_button_text,
                               const std::string& negative_button_text,
                               const std::shared_ptr<AlertListenerInterface>& listener) = 0;



        /**
         * Create a fullscreen message.
         *
         * WARNING: This API consumes HTML/CSS/JS using an embedded browser control.
         * This means it is subject to all the risks of rendering untrusted web pages and running untrusted JS.
         * Treat all calls to this API with caution and make sure input is vetted for safety somewhere.
         *
         * @param html               String html content to be displayed with the message
         * @param fullscreenListener FullscreenListener listener for fullscreen message events
         * @return FullscreenMessage object if the html is valid, null otherwise
         */
        virtual std::shared_ptr<FullScreenMessageUiInterface> CreateFullscreenMessage(const std::string& html,
                const std::shared_ptr<FullscreenListenerInterface>& fullscreenListener) = 0;
        /**
         * Display a local notification
         *
         * @param identifier    String unique identifier for the local notification
         * @param content       String notification message content
         * @param sound         String notification message sound
         * @param category      String notification message category
         * @param delay_seconds int number of seconds to wait before displaying this local notification
         * @param deep_link     String the link to be opened on notification clickthrough
         * @param fire_date     number of seconds from epoch when the local notification should fire
         * @param user_info     String (json) additional data for the local notification
         */
        virtual void ShowLocalNotification(const std::string& identifier,
                                           const std::string& content,
                                           const std::string& sound,
                                           const std::string& category,
                                           std::chrono::seconds delay_seconds,
                                           const std::string& deep_link,
                                           std::chrono::seconds fire_date,
                                           const std::string& user_info) = 0;

        /**
         * Triggers the \p url to be shown by the platform.
         * For example, if this URL contains a http scheme, then the URL will be handled by the system http handler.
         * This API does not require a specific scheme, and will do the best effort to trigger the URL on the platform.
         *
         * @returns true, if the url was successfully shown.
         */
        virtual bool ShowUrl(const std::string& url) = 0;

        /**
         * Creates and returns an instance of UIService.
         *
         */
        static std::shared_ptr<UIServiceInterface> Create();

        /**
         * Get the current application state
         *
         * @return AppState the current application state
         */
        virtual AppState GetAppState() const = 0;

        /**
         * Register application state transition listener
         *
         * @param listener an implementation of AppStateListener
         */
        virtual void RegisterAppStateListener(const std::shared_ptr<AppStateListenerInterface>& listener) = 0;

        /**
         * Unregister application state transition listener
         *
         * @param listener the AppStateListener to unregister
         */
        virtual void UnregisterAppStateListener(const std::shared_ptr<AppStateListenerInterface>& listener) = 0;

        /**
         * Creates a floating button instance
         *
         * @param listener used for tracking UI floating button activity (tap/drag).
         */
        virtual std::shared_ptr<FloatingButtonInterface> CreateFloatingButton(const
                std::shared_ptr<FloatingButtonListenerInterface>&
                listener) = 0;

        /**
         * Returns true if there is another message displayed at this time, false otherwise.
         * The status is collected from the platform messages monitor and it applies if either
         * an alert message or a full screen message is displayed at some point.
         */
        virtual bool IsMessageDisplayed() = 0;
    };
} // namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_UISERVICEINTERFACE_H */
