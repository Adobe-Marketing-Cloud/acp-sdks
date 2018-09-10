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

#if TARGET_OS_IOS
#import <Foundation/Foundation.h>
FOUNDATION_EXPORT double AdobeMarketingMobileCoreVersionNumber;
FOUNDATION_EXPORT const unsigned char AdobeMarketingMobileCoreVersionString[];
#else
extern double AdobeMarketingMobileCoreVersionNumber;
extern const unsigned char AdobeMarketingMobileCoreVersionString[];
#endif

#import <AdobeMarketingMobileCore/BluetoothServiceInterface.h>
#import <AdobeMarketingMobileCore/Common.h>
#import <AdobeMarketingMobileCore/CompressedFileServiceInterface.h>
#import <AdobeMarketingMobileCore/Configuration.h>
#import <AdobeMarketingMobileCore/ContextData.h>
#import <AdobeMarketingMobileCore/Core.h>
#import <AdobeMarketingMobileCore/CryptoServiceInterface.h>
#import <AdobeMarketingMobileCore/DatabaseHitBase.h>
#import <AdobeMarketingMobileCore/DatabaseHitSchema.h>
#import <AdobeMarketingMobileCore/DatabaseHitSchemaBase.h>
#import <AdobeMarketingMobileCore/DatabaseServiceInterface.h>
#import <AdobeMarketingMobileCore/EncodingServiceInterface.h>
#import <AdobeMarketingMobileCore/Event.h>
#import <AdobeMarketingMobileCore/EventBuilder.h>
#import <AdobeMarketingMobileCore/EventData.h>
#import <AdobeMarketingMobileCore/EventHub.h>
#import <AdobeMarketingMobileCore/EventSource.h>
#import <AdobeMarketingMobileCore/EventType.h>
#import <AdobeMarketingMobileCore/Expected.h>
#import <AdobeMarketingMobileCore/ExternalModule.h>
#import <AdobeMarketingMobileCore/ExternalModuleBridge.h>
#import <AdobeMarketingMobileCore/ExternalModuleDispatcher.h>
#import <AdobeMarketingMobileCore/ExternalModuleInterface.h>
#import <AdobeMarketingMobileCore/ExternalModuleListener.h>
#import <AdobeMarketingMobileCore/ExternalModuleListenerInterface.h>
#import <AdobeMarketingMobileCore/ExternalModuleProcessor.h>
#import <AdobeMarketingMobileCore/ExternalModuleProcessorInterface.h>
#import <AdobeMarketingMobileCore/ExternalModuleServicesInterface.h>
#import <AdobeMarketingMobileCore/FileSystemServiceInterface.h>
#import <AdobeMarketingMobileCore/HitDatabaseBase.h>
#import <AdobeMarketingMobileCore/HitProcessor.h>
#import <AdobeMarketingMobileCore/HitProcessorBase.h>
#import <AdobeMarketingMobileCore/HitQueue.h>
#import <AdobeMarketingMobileCore/HitQueueBase.h>
#import <AdobeMarketingMobileCore/HttpConnectionConstants.h>
#import <AdobeMarketingMobileCore/InternalModule.h>
#import <AdobeMarketingMobileCore/JsonArraySerializer.h>
#import <AdobeMarketingMobileCore/JsonObjectSerializer.h>
#import <AdobeMarketingMobileCore/JsonUtilityServiceInterface.h>
#import <AdobeMarketingMobileCore/LaunchType.h>
#import <AdobeMarketingMobileCore/LocalStorageServiceInterface.h>
#import <AdobeMarketingMobileCore/Log.h>
#import <AdobeMarketingMobileCore/LoggingMode.h>
#import <AdobeMarketingMobileCore/LoggingServiceInterface.h>
#import <AdobeMarketingMobileCore/MobilePrivacyStatus.h>
#import <AdobeMarketingMobileCore/Module.h>
#import <AdobeMarketingMobileCore/ModuleEventDispatcher.h>
#import <AdobeMarketingMobileCore/ModuleEventDispatcherBase.h>
#import <AdobeMarketingMobileCore/ModuleEventListener.h>
#import <AdobeMarketingMobileCore/ModuleEventListenerBase.h>
#import <AdobeMarketingMobileCore/ModuleEventProcessor.h>
#import <AdobeMarketingMobileCore/ModuleEventProcessorBase.h>
#import <AdobeMarketingMobileCore/NetworkConnectionUtil.h>
#import <AdobeMarketingMobileCore/NetworkServiceInterface.h>
#import <AdobeMarketingMobileCore/Object.h>
#import <AdobeMarketingMobileCore/ObjectInterface.h>
#import <AdobeMarketingMobileCore/OneTimeListener.h>
#import <AdobeMarketingMobileCore/PeripheralServiceInterface.h>
#import <AdobeMarketingMobileCore/PlatformServicesInterface.h>
#import <AdobeMarketingMobileCore/Query.h>
#import <AdobeMarketingMobileCore/QueryStringBuilder.h>
#import <AdobeMarketingMobileCore/RandomUtil.h>
#import <AdobeMarketingMobileCore/RangedResolver.h>
#import <AdobeMarketingMobileCore/RemoteFileManagerServiceInterface.h>
#import <AdobeMarketingMobileCore/SdkError.h>
#import <AdobeMarketingMobileCore/StringUtils.h>
#import <AdobeMarketingMobileCore/SystemInfoServiceInterface.h>
#import <AdobeMarketingMobileCore/TaskExecutor.h>
#import <AdobeMarketingMobileCore/TaskExecutorInterface.h>
#import <AdobeMarketingMobileCore/TimeUtils.h>
#import <AdobeMarketingMobileCore/Timer.h>
#import <AdobeMarketingMobileCore/UIServiceInterface.h>
#import <AdobeMarketingMobileCore/UrlBuilder.h>
#import <AdobeMarketingMobileCore/UrlEncoder.h>
#import <AdobeMarketingMobileCore/UrlUtil.h>
#import <AdobeMarketingMobileCore/URLServiceInterface.h>
#import <AdobeMarketingMobileCore/Variant.h>
#import <AdobeMarketingMobileCore/VariantKind.h>
#import <AdobeMarketingMobileCore/VariantSerializerInterface.h>


