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

import java.util.Locale;

public class WeatherExtensionDataObject {
    private String conditions;
    private double temperature;

    public WeatherExtensionDataObject(final double temperature, final String conditions) {
        this.temperature = temperature;
        this.conditions = conditions;
    }

    public String getConditions() {
        return conditions;
    }

    public double getTemperature() {
        return temperature;
    }

    @Override
    public String toString() {
        return String.format(Locale.getDefault(), "Temperature: %.2f, Conditions: %s", temperature, conditions);
    }
}
