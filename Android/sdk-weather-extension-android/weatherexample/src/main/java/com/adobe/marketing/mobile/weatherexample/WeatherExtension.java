//
//  Adobe Experience Platform -- ACP SDK Extension for Android
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//

package com.adobe.marketing.mobile.weatherexample;

import android.util.Log;

import com.adobe.marketing.mobile.AdobeCallback;
import com.adobe.marketing.mobile.Event;
import com.adobe.marketing.mobile.ExtensionError;
import com.adobe.marketing.mobile.ExtensionErrorCallback;
import com.adobe.marketing.mobile.MobileCore;

import java.util.HashMap;
import java.util.Map;

public class WeatherExtension {
    private static final String LOG_TAG = WeatherExtension.class.getSimpleName();

    private WeatherExtension() {}

    /**
     * Registers the weather extension. This method should be called once
     */
    public static void registerExtension() {
        MobileCore.registerExtension(WeatherExtensionInternal.class, null);
    }

    /**
     * Gets the current weather and conditions for the provided zip code
     *
     * This method results in an asynchronous network call to get the local weather. Once the network
     * call has received a response, the WeatherExtension class will parse the results and return it
     * via the content parameter in the provided callback block.
     *
     * @param zip {@link String} representing a US postal code
     * @param callback {@link WeatherExtensionCallback} a void callback method which contains the
     *                                                 current weather information
     */
    public static void getWeatherByZipCode(final String zip, final WeatherExtensionCallback<WeatherExtensionDataObject> callback) {
        if (callback == null) {
            Log.w(LOG_TAG, "Weather cannot be returned when callback is null");
            return;
        }

        // create the request event
        Map<String, Object> requestData = new HashMap<>();
        requestData.put("zip", zip);

        final Event getWeatherEvent = new Event.Builder("Get Weather",
                WeatherExtensionConstants.EVENT_TYPE_WEATHER_EXTENSION,
                WeatherExtensionConstants.EVENT_SOURCE_WEATHER_REQUEST_CONTENT).setEventData(requestData).build();

        if (getWeatherEvent == null) {
            Log.d(LOG_TAG, "An error occurred constructing the Get Weather event");
            callback.call(null);
            return;
        }

        // dispatch the event and handle the callback
        AdobeCallback<Event> responseEventCallback = new AdobeCallback<Event>() {
            @Override
            public void call(final Event responseEvent) {
                Log.d(LOG_TAG, String.format("In response callback for event '%s', event data returned: %s",
                        responseEvent.getName(), responseEvent.getEventData()));
                Map<String, Object> eventData = responseEvent.getEventData();
                if (eventData == null || eventData.isEmpty()) {
                    callback.call(null);
                }

                try {
                    Map<String, Object> weather = (Map<String, Object>) eventData.get("weather");
                    double temp = Double.valueOf((String)weather.get("temp"));
                    String conditions = (String) weather.get("conditions");
                    WeatherExtensionDataObject weatherObject = new WeatherExtensionDataObject(temp, conditions);

                    callback.call(weatherObject);
                } catch (Exception exception) {
                    callback.call(null);
                }
            }
        };

        ExtensionErrorCallback<ExtensionError> extensionErrorCallback = new ExtensionErrorCallback<ExtensionError>() {
            @Override
            public void error(final ExtensionError extensionError) {
                Log.e(LOG_TAG, String.format("An error occurred dispatching event '%s', %s", getWeatherEvent.getName(), extensionError.getErrorName()));
            }
        };

        if (MobileCore.dispatchEventWithResponseCallback(getWeatherEvent, responseEventCallback, extensionErrorCallback)) {
            Log.d(LOG_TAG, String.format("WeatherExtension dispatched an event '%s'", getWeatherEvent.getName()));
        }
    }
}
