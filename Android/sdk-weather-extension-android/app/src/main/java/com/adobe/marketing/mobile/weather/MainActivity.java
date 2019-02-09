//
//  Adobe Experience Platform -- ACP SDK Extension for Android
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//

package com.adobe.marketing.mobile.weather;

import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.TextView;
import com.adobe.marketing.mobile.MobileCore;
import com.adobe.marketing.mobile.weatherexample.WeatherExtension;
import com.adobe.marketing.mobile.weatherexample.WeatherExtensionCallback;
import com.adobe.marketing.mobile.weatherexample.WeatherExtensionDataObject;

import java.util.HashMap;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private final String LOG_TAG = MainActivity.class.getSimpleName();

    /**
     *  sample zip codes:
     *  -------------------
     *  Times Square, NY - 10036
     *  Lehi, UT - 84043
     *  Beverly Hills, CA - 90210
     *  Fairbanks, AK - 99703
     */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public void onResume() {
        super.onResume();
        MobileCore.lifecycleStart(null);
    }

    @Override
    public void onPause() {
        super.onPause();
        MobileCore.lifecyclePause();
    }

    public void onGetWeatherClick(final View view) {
        EditText editTextZipCode = findViewById(R.id.etZipcode);
        hideKeyboard(editTextZipCode);
        if (editTextZipCode == null || editTextZipCode.getText() == null) {
            return;
        }

        String zipcode = editTextZipCode.getText().toString();

        try {
            Integer.valueOf(zipcode);
        } catch (NumberFormatException exception) {
            Log.w(LOG_TAG, "The zip code should be valid US zip code value");
            return;
        }

        WeatherExtension.getWeatherByZipCode(zipcode, new WeatherExtensionCallback<WeatherExtensionDataObject>() {
            @Override
            public void call(final WeatherExtensionDataObject weatherObject) {
                if (weatherObject == null) {
                    Log.d(LOG_TAG, "Received weather response was null");
                    return;
                }
                Log.d(LOG_TAG, String.format("Received weather response: %s", weatherObject.toString()));

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        TextView textViewTemperature = findViewById(R.id.tvTemperature);
                        textViewTemperature.setText(String.valueOf((int)weatherObject.getTemperature()));

                        TextView textViewConditions = findViewById(R.id.tvConditions);
                        textViewConditions.setText(weatherObject.getConditions());
                    }
                });
            }
        });
    }

    public void onGetWeatherByTriggeringRules(final View view) {
        String currentZipCode = getZipCode();
        if (currentZipCode == null) {
            return;
        }

        /*
         * Send a track action hit in order to trigger rules configured in Launch UI based on
         * MobileCore TrackAction events. When the rule is triggered, a new response content rules
         * consequence event will be dispatched by Rules Engine and processed by the WeatherExtension
         */
        Map<String, String> contextData = new HashMap<>();
        contextData.put("zip", currentZipCode);
        MobileCore.trackAction("GetWeatherByTriggeringRulesBtnClicked", contextData);
    }

    private String getZipCode() {
        EditText editTextZipCode = findViewById(R.id.etZipcode);
        if (editTextZipCode.getText() == null) {
            return null;
        }

        String zipCode = editTextZipCode.getText().toString();

        try {
            Integer.valueOf(zipCode);
        } catch (NumberFormatException exception) {
            Log.w(LOG_TAG, "The zip code should be valid US zip code value");
            return null;
        }

        return zipCode;
    }

    private void hideKeyboard(final EditText editText) {
        InputMethodManager inputMethodManager = (InputMethodManager)getSystemService(Context.INPUT_METHOD_SERVICE);
        if (inputMethodManager != null && editText != null) {
            inputMethodManager.hideSoftInputFromWindow(editText.getWindowToken(), 0);
        }
    }
}
