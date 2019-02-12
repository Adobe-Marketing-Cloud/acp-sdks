//
//  Adobe Experience Platform -- ACP SDK Extension for Android
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//

package com.adobe.marketing.mobile.weatherexample;

class WeatherExtensionConstants {
    static final String EVENT_TYPE_WEATHER_EXTENSION = "com.acpExample.eventType.weatherExtension";
    static final String EVENT_TYPE_ADOBE_RULES_ENGINE = "com.adobe.eventType.rulesEngine";
    static final String EVENT_TYPE_ADOBE_HUB = "com.adobe.eventType.hub";
    static final String EVENT_SOURCE_WEATHER_REQUEST_CONTENT = "com.acpExample.eventSource.requestContent";
    static final String EVENT_SOURCE_WEATHER_RESPONSE_CONTENT = "com.acpExample.eventSource.responseContent";
    static final String EVENT_SOURCE_ADOBE_RESPONSE_CONTENT = "com.adobe.eventSource.responseContent";
    static final String EVENT_SOURCE_ADOBE_SHARED_STATE = "com.adobe.eventSource.sharedState";

    class SharedState {
        static final String STATE_OWNER = "stateowner";
        static final String CONFIGURATION = "com.adobe.module.configuration";
        static final String IDENTITY = "com.adobe.module.identity";

        private SharedState(){}
    }

    private WeatherExtensionConstants(){}
}
