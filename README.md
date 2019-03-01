# Adobe Experience Platform SDKs
Home of the official Adobe Experience Platform (AEP) SDKs for mobile apps.

<hr>

[Adobe Launch](https://launch.adobe.com/) and Adobe Experience Platform SDKs are coming together to help you take advantage of [Adobe's Experience Cloud](https://www.adobe.com/experience-cloud.html) in your mobile app.

<img src="resources/acp_sdks.png"></img>

To learn more about your topic of interest, click the following links:

- [Adobe Experience Platform SDK documentation](https://aep-sdks.gitbook.io/docs/)
- [Launch documentation](https://docs.adobelaunch.com/)
- [Mobile on Launch forums](https://forums.adobe.com/community/experience-cloud/platform/launch/sdk)

# Latest Versions

| Extension | Cocopods | Maven | Github |
| :--- | :--- | :--- | :--- |
| [Mobile Core](../../using-mobile-extensions/mobile-core/) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPCore.svg?color=dd0000&label=pod%20ACPCore&style=popout) | [![Version](https://img.shields.io/maven-central/v/com.adobe.marketing.mobile/sdk-core.svg?style=plastic)](https://mvnrepository.com/artifact/com.adobe.marketing.mobile/sdk-core) | [Android](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/android) \| [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPCore) |
| [Adobe Analytics](../../using-mobile-extensions/adobe-analytics/) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPAnalytics.svg?color=dd0000&label=pod%20ACPAnalytics&style=popout) | [![Version](https://img.shields.io/maven-central/v/com.adobe.marketing.mobile/analytics.svg?style=plastic)](https://mvnrepository.com/artifact/com.adobe.marketing.mobile/analytics) | [Android](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/android) \| [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPAnalytics) |
| [Adobe Media Analytics for Audio & Video](../../using-mobile-extensions/adobe-media-analytics/) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPMedia.svg?color=dd0000&label=pod%20ACPMedia&style=popout) | [![Version](https://img.shields.io/maven-central/v/com.adobe.marketing.mobile/media.svg?style=plastic)](https://mvnrepository.com/artifact/com.adobe.marketing.mobile/media) | [Android](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/android) \| [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPMedia) |
| [Adobe Audience Manager](../../using-mobile-extensions/adobe-audience-manager/) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPAudience.svg?color=dd0000&label=pod%20ACPAudience&style=popout) | [![Version](https://img.shields.io/maven-central/v/com.adobe.marketing.mobile/audience.svg?style=plastic)](https://mvnrepository.com/artifact/com.adobe.marketing.mobile/audience) | [Android](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/android) \| [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPAudience) |
| [Adobe Campaign Classic](../../using-mobile-extensions/adobe-campaignclassic/) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPCampaignClassic.svg?color=dd0000&label=pod%20ACPCampaignClassic&style=popout) | [![Version](https://img.shields.io/maven-central/v/com.adobe.marketing.mobile/campaignclassic.svg?style=plastic)](https://mvnrepository.com/artifact/com.adobe.marketing.mobile/campaignclassic) | [Android](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/android) \| [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPCampaignClassic) |
| [Adobe Campaign Standard](../../using-mobile-extensions/adobe-campaign-standard/) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPCampaign.svg?color=dd0000&label=pod%20ACPCampaign&style=popout) | Releasing Shortly | [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPCampaign) |
| [Adobe Target](../../using-mobile-extensions/adobe-target/) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPTarget.svg?color=dd0000&label=pod%20ACPTarget&style=popout) | [![Version](https://img.shields.io/maven-central/v/com.adobe.marketing.mobile/target.svg?style=plastic)](https://mvnrepository.com/artifact/com.adobe.marketing.mobile/target) | [Android](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/android) \| [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPTarget) |
| [Profile](../../using-mobile-extensions/profile/) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPUserProfile.svg?color=dd0000&label=pod%20ACPUserProfile&style=popout) | [![Version](https://img.shields.io/maven-central/v/com.adobe.marketing.mobile/userprofile.svg?style=plastic)](https://mvnrepository.com/artifact/com.adobe.marketing.mobile/userprofile) | [Android](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/android) \| [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPUserProfile) | 
| [Places](https://launch.gitbook.io/launch-adobe-mobile-sdk-beta/v/places/extension-reference/places-extension) | ![Cocoapods](https://img.shields.io/cocoapods/v/ACPPlaces.svg?color=dd0000&label=pod%20ACPPlaces&style=popout) | Releasing Shortly | [iOS](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/master/iOS/ACPPlaces) |


## Installing the AEP SDK for Android

The AEP SDK supports Android API 14 (Ice Cream Sandwich) and newer.

#### <a name="gradle"></a>Installation using Maven/Gradle << Preferred >>
Installation via [Maven](https://maven.apache.org/) & [Gradle](https://gradle.org/) is the easiest and recommended way to get the AEP SDK into your Android app.  In your `build.gradle` file, include the following dependencies:

    implementation 'com.adobe.marketing.mobile:sdk-core:1.+'
    implementation 'com.adobe.marketing.mobile:analytics:1.+'
    implementation 'com.adobe.marketing.mobile:audience:1.+'
    implementation 'com.adobe.marketing.mobile:target:1.+'
    implementation 'com.adobe.marketing.mobile:userprofile:1.+'

#### <a name="manual-android"></a>Manual installation
In order to do a manual installation of the AEP SDK `.aar` binaries, please complete the following steps for each `.aar` you need:
- Download the `.aar` file from the `Android/` directory on the `master` branch.
- Go to "File > New > New Module" in the menu.
- Select the "Import .JAR/.AAR Package" from the New Module window.
- In the "Import Module from Library" dialog, enter the path to the `.aar` you are installing.
   - Enter a Subproject Name of your choice.
- Click "Finish".
- Once Gradle sync is complete and you see the library as a module in the Android project view, add the new library module as a dependency to your app.
   - Right-click on your app module, and select "Open Module Settings".
   - In the next dialog, select your app and click on the "Dependencies" tab.
   - Click on the "+" button on the bottom, and select module dependency.
   - In the next dialog, select the library module as your dependency.

__Important__ - note that all AEP SDK Android binaries depend on `core-1.x.x.aar`.

## Installing the AEP SDK for iOS

The AEP SDK supports iOS 10 and newer.

#### <a name="cocoapods"></a>Installation using Cocoapods << Preferred >>
Installation via [Cocoapods](https://cocoapods.org/) is the easiest and recommended way to get the AEP SDK into your iOS app.  In your `Podfile`, simply add the following changes as needed:

    # minimum supported version of iOS is 10.0
    platform :ios, '10.0'    

    # Uncomment the next line if you're using Swift or would like to use dynamic frameworks
    # use_frameworks!
    
    # Adobe ACP Pods
    pod 'ACPCore', '~> 2.0'
    pod 'ACPAnalytics', '~> 2.0'
    pod 'ACPAudience', '~> 2.0'
    pod 'ACPTarget', '~> 2.0'
    pod 'ACPUserProfile', '~> 2.0'


#### <a name="manual-ios"></a>Manual installation
In order to do a manual installation of the AEP SDK libraries, please complete the following steps:
- Download the extensions needed by your app from the `iOS/` directory.
- In the Xcode project create a new Group, and then drag all the folders you just download and drop them under the group. And verify the following:
    * `The Copy Items if needed checkbox` is selected.
    * `Create groups` is selected.
    * In the`Add to targets` section select all the targets that need AEP SDKs.
- Select your project from the `Project Navigator`, select your App from the `TARGETS` frame, then select the `General` tab at the top of the window.
- In the `Link Binary With Libraries` section, click the `+` link and add the following frameworks and libraries: `UIKit`, `SystemConfiguration`, `WebKit`, `UserNotifications`, `libsqlite3.0`, `libc++`, `libz`.

__Important__ - note that all AEP SDK iOS libraries depend on `libACPCore.a`.
