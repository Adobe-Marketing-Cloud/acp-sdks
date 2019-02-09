//
//  Adobe Experience Platform -- ACP SDK Extension for Android
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//

package com.adobe.marketing.mobile.weather;

import android.app.Application;
import android.util.Log;
import com.adobe.marketing.mobile.*;
import com.adobe.marketing.mobile.weatherexample.WeatherExtension;

import java.util.HashMap;
import java.util.Map;

public class WeatherTesterApp extends Application {
    private final String LOG_TAG = WeatherTesterApp.class.getSimpleName();

    // TODO: fill in your API key here
    private final String WEATHER_EXAMPLE_API_KEY = "";

    @Override
    public void onCreate() {
        super.onCreate();
        MobileCore.setApplication(this);

        // set the environment id associated with your Launch mobile property
        MobileCore.configureWithAppID("staging/launch-ENb44c5c8eb4ac4c5b8c89b6afffc167f7-development");
        MobileCore.setLogLevel(LoggingMode.VERBOSE);

        // register Adobe core extensions
        try {
            Identity.registerExtension();
            Signal.registerExtension();
            Lifecycle.registerExtension();
            Analytics.registerExtension();
        } catch (InvalidInitException e) {
            e.printStackTrace();
        }

        // register the Weather extension
        WeatherExtension.registerExtension();

        // once all the extensions are registered, call MobileCore.start(...) to start processing the events
        MobileCore.start(new AdobeCallback() {
            @Override
            public void call(final Object o) {
                // if you need to update the configuration programmatically, you can use the
                // MobileCore.updateConfiguration API
                Map<String, Object> weatherExtensionConfiguration = new HashMap<>();
                weatherExtensionConfiguration.put("weather.apiKey", WEATHER_EXAMPLE_API_KEY);
                MobileCore.updateConfiguration(weatherExtensionConfiguration);

                Log.d(LOG_TAG, "Mobile SDK was initialized");
            }
        });
    }
}
