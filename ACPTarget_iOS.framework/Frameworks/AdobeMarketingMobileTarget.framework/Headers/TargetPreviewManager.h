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

#ifndef ADOBEMOBILE_TARGET_TARGETPREVIEWMANAGER_H
#define ADOBEMOBILE_TARGET_TARGETPREVIEWMANAGER_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include <vector>
#include <map>
#include <string>

namespace AdobeMarketingMobile {
    class Target;

    /**
     * This class can be used to handle the preview mode
     */
    class TargetPreviewManager : public Object {

    public:
        explicit TargetPreviewManager(const std::shared_ptr<NetworkServiceInterface>& network_service,
                                      const std::shared_ptr<UIServiceInterface>& ui_service,
                                      const std::shared_ptr<URLServiceInterface>& url_service);

        /**
         * Starts the preview mode by parsing the preview deep link, fetching the webview from target, displaying
         * the preview button and creating a new custom message for the preview view.
         */
        ADOBE_VIRTUAL_FOR_TESTS void EnterPreviewModeWithDeepLinkParams(const std::string& client_code,
                const std::string& deep_link);

        /**
         * Should be called when the preview message is closed; it resets all the target preview properties;
         */
        ADOBE_VIRTUAL_FOR_TESTS void ResetTargetPreviewProperties();

        /**
         * This method will be called by the TargetPreviewMessageListener to process given url.
         * If it is a cancel url, it dismisses the message and exits preview mode.
         * If it is a confirm url, it dismisses the message, updates preview parameters and starts a
         * new view if preview restart url is set
         */
        ADOBE_VIRTUAL_FOR_TESTS bool PreviewConfirmedWithUrl(const std::shared_ptr<FullScreenMessageUiInterface>& message,
                const std::string& url);

        /**
         * If there is no other fetching in progress, it initiates a new async request to target.
         * If the connection is successfull and a valid response is received, a full screen message will
         * be created and displayed. This method will be called for preview deeplinks or preview button tap
         * detection
         */
        ADOBE_VIRTUAL_FOR_TESTS void FetchWebView();

        /**
         * Returns current preview parameters representing the json received from target servers as a string,
         * or empty string if preview mode was reset
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetPreviewParameters();

        /**
         * Return current preview token if available or empty string if preview mode was reset
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetPreviewToken();

        ADOBE_VIRTUAL_FOR_TESTS void SetRestartDeepLink(const std::string& restart_deeplink);

    private:

        /**
         * Extracts token and endpoint parameters if present in the deeplink query params map and sets them
         * in local variables for later user.
         */
        void SetupTargetPreviewParameters(std::map<std::string, std::string>& preview_params);

        /**
         * Creates an instance of floating button if necessary.
         */
        void SetupTargetPreviewFloatingButton();

        std::string GetUrlForTargetPreviewRequest();
        void CreateAndShowMessage();
        std::shared_ptr<NetworkServiceInterface> network_service_;
        std::shared_ptr<UIServiceInterface> ui_service_;
        std::shared_ptr<URLServiceInterface> url_service_;

        std::string preview_params_;
        std::string token_;
        std::string endpoint_;
        std::string web_view_html_;
        std::string restart_url_;
        bool fetching_web_view_;
        std::string client_code_;
        std::shared_ptr<FloatingButtonInterface> preview_button_;
    };

    class PreviewButtonListener : public Object, public virtual FloatingButtonListenerInterface {
    public:
        explicit PreviewButtonListener(const std::shared_ptr<TargetPreviewManager>& target_preview_manager);

        /**
         * @private
         * @see FloatingButtonListenerInterface::OnTapDetected()
         */
        void OnTapDetected();

        /**
         * @private
         * @see FloatingButtonListenerInterface::OnPanDetected()
         */
        void OnPanDetected() {}

    private:
        std::shared_ptr<TargetPreviewManager> target_preview_manager_;
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETPREVIEWMANAGER_H */

