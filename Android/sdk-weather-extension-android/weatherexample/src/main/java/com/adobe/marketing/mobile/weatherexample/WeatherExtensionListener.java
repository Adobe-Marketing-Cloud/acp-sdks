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

import com.adobe.marketing.mobile.Event;
import com.adobe.marketing.mobile.ExtensionApi;
import com.adobe.marketing.mobile.ExtensionListener;

class WeatherExtensionListener extends ExtensionListener {
    protected WeatherExtensionListener(final ExtensionApi extension, final String type, final String source) {
        super(extension, type, source);
    }

    @Override
    public void hear(final Event event) {
        if (event.getEventData() == null) {
            return;
        }

        final WeatherExtensionInternal parentExtension = getParentExtension();
        if (parentExtension == null) {
            return;
        }

        // handle SharedState events
        if (WeatherExtensionConstants.EVENT_TYPE_ADOBE_HUB.equalsIgnoreCase(event.getType())) {
            if (WeatherExtensionConstants.SharedState.CONFIGURATION.
                    equalsIgnoreCase((String)event.getEventData().get(WeatherExtensionConstants.SharedState.STATE_OWNER))) {
                getParentExtension().getExecutor().execute(new Runnable() {
                    @Override
                    public void run() {
                        parentExtension.processEvents();
                    }
                });
            }
        } else if (WeatherExtensionConstants.EVENT_TYPE_WEATHER_EXTENSION.equalsIgnoreCase(event.getType())) {
            // handle WeatherExtension events
            getParentExtension().getExecutor().execute(new Runnable() {
                @Override
                public void run() {
                    parentExtension.queueEvent(event);
                    parentExtension.processEvents();
                }
            });
        } else if (WeatherExtensionConstants.EVENT_TYPE_ADOBE_RULES_ENGINE.equalsIgnoreCase(event.getType()) &&
                WeatherExtensionConstants.EVENT_SOURCE_ADOBE_RESPONSE_CONTENT.equalsIgnoreCase(event.getSource())) {
            // handle Rules Consequences
            getParentExtension().getExecutor().execute(new Runnable() {
                @Override
                public void run() {
                    parentExtension.queueEvent(event);
                    parentExtension.processEvents();
                }
            });
        }
    }

    @Override
    protected WeatherExtensionInternal getParentExtension() {
        return (WeatherExtensionInternal) super.getParentExtension();
    }
}
