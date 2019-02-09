//
//  Adobe Experience Platform -- ACP SDK Extension for Android
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//

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
