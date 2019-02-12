//
//  Adobe Experience Platform -- ACP SDK Extension for Android
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//

package com.adobe.marketing.mobile.weatherexample;

import com.adobe.marketing.mobile.AdobeCallback;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;

import javax.net.ssl.HttpsURLConnection;

class WeatherExtensionApiHandler {
    private static final int STREAM_WRITE_BUFFER_SIZE = 512;
    private static final String UTF_8 = "UTF-8";
    private static final String WEATHER_TEMPERATURE_KEY = "temp";
    private static final String WEATHER_CONDITIONS_KEY = "conditions";
    private static final int CONNECTION_TIMEOUT = 3000;

    /**
     * Makes a network call and returns a map with the temperature and conditions for the provided zip code
     * in the following format:
     * {
     *  "temp" : 47.1,
     *  "conditions" : "Clear"
     * }
     */
    void getWeatherForZip(final String zip, final String apiKey, final AdobeCallback<Map<String, Object>> callback) {
        if (callback == null) {
            return;
        }

        String urlString = String.format("https://api.openweathermap.org/data/2.5/weather?zip=%s,us&units=imperial&APPID=%s", zip, apiKey);
        URL url = null;
        try {
            url = new URL(urlString);
        } catch (MalformedURLException exception) {
            callback.call(null);
        }

        if (url == null) {
            callback.call(null);
            return;
        }

        String networkResponse;
        try {
             networkResponse = networkRequest(url);
             callback.call(getWeatherResponse(networkResponse));
        } catch (IOException e) {
            e.printStackTrace();
            callback.call(null);
        }
    }

    private String networkRequest(final URL url) throws IOException {
        InputStream stream = null;
        HttpsURLConnection connection = null;
        String result;
        try {
            connection = (HttpsURLConnection) url.openConnection();
            connection.setReadTimeout(CONNECTION_TIMEOUT);
            connection.setConnectTimeout(CONNECTION_TIMEOUT);
            connection.setRequestMethod("GET");
            connection.setDoInput(true);

            connection.connect();
            int responseCode = connection.getResponseCode();
            if (responseCode != HttpsURLConnection.HTTP_OK) {
                throw new IOException("HTTP error code: " + responseCode);
            }

            final byte[] buffer = new byte[STREAM_WRITE_BUFFER_SIZE];
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            stream = connection.getInputStream();
            int len;
            while ((len = stream.read(buffer)) != -1) {
                out.write(buffer, 0, len);
            }
            result = out.toString(UTF_8);

        } finally {
            // close stream and disconnect HTTPS connection.
            if (stream != null) {
                stream.close();
            }
            if (connection != null) {
                connection.disconnect();
            }
        }
        return result;
    }

    private Map<String, Object> getWeatherResponse(final String serverResponse) {
        if (serverResponse == null) {
            return null;
        }

        try {
            JSONObject jsonResponse = new JSONObject(serverResponse);
            JSONObject mainData = jsonResponse.getJSONObject("main");
            String temp = String.format("%.2f", mainData.getDouble("temp"));
            JSONObject conditionsData = jsonResponse.getJSONArray("weather").getJSONObject(0);
            String conditions = conditionsData.getString("main");

            Map<String, Object> returnedWeather = new HashMap<>();
            returnedWeather.put(WEATHER_TEMPERATURE_KEY, temp);
            returnedWeather.put(WEATHER_CONDITIONS_KEY, conditions);
            return returnedWeather;

        } catch (JSONException e) {
            e.printStackTrace();
        }

        return null;
    }
}
