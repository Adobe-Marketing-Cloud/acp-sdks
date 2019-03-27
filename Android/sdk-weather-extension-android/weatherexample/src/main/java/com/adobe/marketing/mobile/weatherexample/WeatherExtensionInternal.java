/*
 ADOBE CONFIDENTIAL

 Copyright 2019 Adobe
 All Rights Reserved.

 NOTICE: Adobe permits you to use, modify, and distribute this file in
 accordance with the terms of the Adobe license agreement accompanying
 it. If you have received this file from a source other than Adobe,
 then your use, modification, or distribution of it requires the prior
 written permission of Adobe.
 */

package com.adobe.marketing.mobile.weatherexample;

import android.util.Log;

import com.adobe.marketing.mobile.AdobeCallback;
import com.adobe.marketing.mobile.Event;
import com.adobe.marketing.mobile.Extension;
import com.adobe.marketing.mobile.ExtensionApi;
import com.adobe.marketing.mobile.ExtensionError;
import com.adobe.marketing.mobile.ExtensionErrorCallback;
import com.adobe.marketing.mobile.ExtensionUnexpectedError;
import com.adobe.marketing.mobile.MobileCore;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class WeatherExtensionInternal extends Extension {

    private static final String IDENTITY_MID_KEY = "mid";
    private static final String RULES_TRIGGERED_CONSEQUENCE_KEY = "triggeredconsequence";
    private static final String RULES_DETAIL_KEY = "detail";
    private static final String WEATHER_API_KEY = "weather.apiKey";
    private static final String WEATHER_ZIP_KEY = "zip";
    private static final String WEATHER_KEY = "weather";

    private ConcurrentLinkedQueue<Event> eventQueue;
    private WeatherExtensionApiHandler apiHandler;
    private ExecutorService executorService;
    private final Object executorMutex = new Object();
    private String mid;

    protected WeatherExtensionInternal(final ExtensionApi extensionApi) {
        super(extensionApi);

        // register a listener for shared state changes
        extensionApi.registerEventListener(
                WeatherExtensionConstants.EVENT_TYPE_ADOBE_HUB,
                WeatherExtensionConstants.EVENT_SOURCE_ADOBE_SHARED_STATE,
                WeatherExtensionListener.class, null);

        // register a listener for RulesEngine response events
        extensionApi.registerEventListener(
                WeatherExtensionConstants.EVENT_TYPE_ADOBE_RULES_ENGINE,
                WeatherExtensionConstants.EVENT_SOURCE_ADOBE_RESPONSE_CONTENT,
                WeatherExtensionListener.class, null);

        // register a listener for WeatherExtension request events
        extensionApi.registerEventListener(
                WeatherExtensionConstants.EVENT_TYPE_WEATHER_EXTENSION,
                WeatherExtensionConstants.EVENT_SOURCE_WEATHER_REQUEST_CONTENT,
                WeatherExtensionListener.class, null);

        // initialize the events queue
        eventQueue = new ConcurrentLinkedQueue<>();
        apiHandler = new WeatherExtensionApiHandler();
    }

    @Override
    protected String getName() {
        return "com.acpExample.weatherExtension";
    }

    @Override
    protected String getVersion() {
        return "1.0.0";
    }

    @Override
    protected void onUnregistered() {
        super.onUnregistered();

        // the extension was unregistered
        // if the shared states are not used in the next registration they can be cleared in this method
        getApi().clearSharedEventStates(null);
        mid = null;
    }

    @Override
    protected void onUnexpectedError(final ExtensionUnexpectedError unexpectedError) {
        super.onUnexpectedError(unexpectedError);
    }

    protected void queueEvent(final Event event) {
        if (event == null) {
            return;
        }

        eventQueue.add(event);
    }

    protected void processEvents() {
        while (!eventQueue.isEmpty()) {
            Event eventToProcess = eventQueue.peek();

            ExtensionErrorCallback<ExtensionError> extensionErrorCallback = new ExtensionErrorCallback<ExtensionError>() {
                @Override
                public void error(final ExtensionError extensionError) {
                    Log.e(getName(), String.format("Could not process event, an error occurred while retrieving configuration shared state: %s", extensionError.getErrorName()));
                }
            };
            Map<String, Object> configSharedState = getApi().getSharedEventState(WeatherExtensionConstants.SharedState.CONFIGURATION, eventToProcess, extensionErrorCallback);

            // NOTE: configuration is mandatory processing the event, so if shared state is null (pending) stop processing events
            if (configSharedState == null) {
                Log.d(getName(), "Could not process event, configuration shared state is pending");
                return;
            }

            String apiKey = configSharedState.isEmpty() ? "" : (String)configSharedState.get(WEATHER_API_KEY);

            // Identity is not a mandatory dependency for this event, just retrieve mid
            extractMidFromIdentitySharedState(eventToProcess);

            if (WeatherExtensionConstants.EVENT_TYPE_WEATHER_EXTENSION.equalsIgnoreCase(eventToProcess.getType())) {
                // handle the get weather event
                handleGetWeatherEvent(eventToProcess, apiKey);
                Log.d(getName(), "GetWeather event successfully processed");
            } else if (WeatherExtensionConstants.EVENT_TYPE_ADOBE_RULES_ENGINE.equalsIgnoreCase(eventToProcess.getType())) {
                // handle the rules consequence
                handleRulesConsequence(eventToProcess, apiKey);
                Log.d(getName(), "Rules consequence event successfully processed");
            }

            // event processed, remove it from the queue
            eventQueue.poll();
        }
    }

    private void handleGetWeatherEvent(final Event event, final String apiKey) {
        Log.d(getName(), "Handling Get Weather event");
        String zip = (String) event.getEventData().get(WEATHER_ZIP_KEY);

        apiHandler.getWeatherForZip(zip, apiKey, new AdobeCallback<Map<String, Object>>(){

            @Override
            public void call(final Map<String, Object> content) {
                // create the response event
                Log.d(getName(),String.format("Weather object returned: %s", content));
                Map<String, Object> eventData = new HashMap<>();
                eventData.put(WEATHER_KEY, content);
                Event weatherLoadedEvent = new Event.Builder("Weather Loaded",
                        WeatherExtensionConstants.EVENT_TYPE_WEATHER_EXTENSION,
                        WeatherExtensionConstants.EVENT_SOURCE_WEATHER_RESPONSE_CONTENT)
                    .setEventData(eventData).build();

                if (weatherLoadedEvent == null) {
                    Log.w(getName(), "An error occurred constructing event");
                }

                // update weather extension's shared state
                getApi().setSharedEventState(content, event, null);

                // dispatch the response for the public API
                ExtensionErrorCallback<ExtensionError> errorCallback = new ExtensionErrorCallback<ExtensionError>() {
                    @Override
                    public void error(final ExtensionError e) {
                        Log.w(getName(), String.format("An error occurred dispatching the weather loaded event: %s", e.getErrorName()));
                    }
                };
                MobileCore.dispatchResponseEvent(weatherLoadedEvent, event, errorCallback);
            }
        });
    }

    private void handleRulesConsequence(final Event event, final String apiKey) {
        Log.d(getName(), "Handling Triggered Consequence event");
        Map<String, Object> eventData = event.getEventData();

        Map<String, Object> triggeredConsequence = (HashMap<String, Object>) eventData.get(RULES_TRIGGERED_CONSEQUENCE_KEY);
        if (triggeredConsequence == null || triggeredConsequence.isEmpty()) {
            return;
        }

        Map<String, Object> detail = (Map<String, Object>)triggeredConsequence.get(RULES_DETAIL_KEY);
        if (detail == null || detail.isEmpty()) {
            return;
        }

        String zip = (String) detail.get(WEATHER_ZIP_KEY);
        if (zip == null) {
            Log.d(getName(), "Not a zip request consequence");
            return;
        }

        apiHandler.getWeatherForZip(zip, apiKey, new AdobeCallback<Map<String, Object>>() {

            @Override
            public void call(final Map<String, Object> content) {
                Log.d(getName(),String.format("The weather has been updated for this user: %s, %s", content.get("temp"), content.get("conditions")));
                // update weather extension's shared state

                ExtensionErrorCallback<ExtensionError> setSharedStateError = new ExtensionErrorCallback<ExtensionError>() {
                    @Override
                    public void error(ExtensionError extensionError) {
                        Log.e(getName(), String.format("An error occurred while setting the shared state %s, error %s", content, extensionError.getErrorName()));
                    }
                };

                getApi().setSharedEventState(content, event,  setSharedStateError);
            }
        });
    }

    private void extractMidFromIdentitySharedState(final Event event) {
        Map<String, Object> identitySharedState = getApi().getSharedEventState(WeatherExtensionConstants.SharedState.IDENTITY, event, null);

        if (identitySharedState == null) {
            Log.d(getName(), "Identity shared state is pending, returning nil");
            return;
        }

        this.mid = (String) identitySharedState.get(IDENTITY_MID_KEY);
    }

    protected final ExecutorService getExecutor() {
        synchronized (executorMutex) {
            if (executorService == null) {
                executorService = Executors.newSingleThreadExecutor();
            }

            return executorService;
        }
    }
}
