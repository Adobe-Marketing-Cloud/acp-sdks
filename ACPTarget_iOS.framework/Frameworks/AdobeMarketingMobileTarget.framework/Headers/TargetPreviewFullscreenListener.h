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


#ifndef ADOBEMOBILE_TARGET_TARGETPREVIEWFULLSCREENLISTENER_H
#define ADOBEMOBILE_TARGET_TARGETPREVIEWFULLSCREENLISTENER_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

namespace AdobeMarketingMobile {
    class TargetPreviewManager;

    /**
     * UI Listener for TargetPreview fullscreen message
     */
    class TargetPreviewFullscreenListener : public Object, public virtual FullscreenListenerInterface {
    public:
        explicit TargetPreviewFullscreenListener(const std::shared_ptr<TargetPreviewManager>& target_preview_manager);

        /**
         * @private
         * @see FullScreenListenerInterface::OnShow()
         */
        void OnShow(const std::shared_ptr<FullScreenMessageUiInterface>& message) override;

        /**
         * @private
         * @see FullScreenListenerInterface::OnDismiss()
         */
        void OnDismiss(const std::shared_ptr<FullScreenMessageUiInterface>& message) override;

        /**
         * @private
         * @see FullScreenListenerInterface::OverrideUrlLoad()
         */
        bool OverrideUrlLoad(const std::shared_ptr<FullScreenMessageUiInterface>& message, const std::string& url) override;

    private:
        std::shared_ptr<TargetPreviewManager> target_preview_manager_;
    };
} // namespace

#endif /* ADOBEMOBILE_TARGET_TARGETPREVIEWFULLSCREENLISTENER_H */
