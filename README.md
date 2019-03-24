# ACPWeatherExample
The Weather Example project is a simple demonstration of how you can write your own custom extension to integrate with the Adobe Experience Platform Mobile SDK and other third party mobile extensions.

<hr>

## iOS - Getting Started

**Prerequisites**

- Xcode v10.x and iPhone Simulator running iOS 10+.

**How to run the project**

1. Download or clone the [weather-example branch](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/weather-example)
2. Navigate to the `iOS/ACPWeatherExample` directory in terminal and run `pod update`
3. Open `ACPWeatherExample.xcworkspace`
4. The `ACPWeatherExample` project has two targets in it:
  - `ACPWeatherExample` - a target to produce a static library output
  - `TestApp` - a simple app used for testing the `ACPWeatherExample` extension with the Adobe Mobile SDK
5. If you want to run the test app, do the following:
  - Go to https://openweathermap.org/ and generate an API key
  - In `AppDelegate.m` for the `TestApp`, fill in the value of `ACPWeatherExampleApiKey` with your API key
  - Select the `TestApp` scheme and press `Run`

## Android - Getting Started

**Prerequisites**

- Android Studio 3.+ with an Android emulator running Android 7.0+
- Gradle 4.4+

**How to run the project**

1. Download or clone the [weather-example branch](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/weather-example)
2. Navigate to the `/Android/sdk-weather-extension-android` directory and open the `settings.gradle` file as a project in Android Studio.
3. Sync the gradle project in order to download the required dependencies.
4. The `sdk-weather-extension-android` project has two modules in it:

- `weatherexample` - produces an Android library
- `app` - a simple app used for testing the `WeatherExample` extension with the Adobe Mobile SDK

5. If you want to run the test app, do the following:

- Go to https://openweathermap.org/ and generate an API key
- In `WeatherTesterApp.java`, fill in the value of `WEATHER_EXAMPLE_API_KEY` with your API key
- Select the `app` Run Configuration and press `Run`

## Extension Documentation

[View the SDK Documentation](https://aep-sdks.gitbook.io/docs/resources/building-mobile-extensions) for information on how to build your own extension.

## Next Steps

Beyond this client-side extension, take some time to explore the Launch UI extension to see how you can define Configuration keys, Data Elements, Events, Conditions and Actions that are all used in the Launch rules engine. 

[Here](https://github.com/Adobe-Marketing-Cloud/reactor-mobile-examples) you can find an example of how to write the Launch UI mobile extension associated with your client-side extension.

## Resources

There is a great deal of information available to learn more about the Adobe Experience Platform Mobile SDK and Launch. Below are some resources that may be helpful:

- [Adobe Mobile SDK documentation and extension developer guide](https://aep-sdks.gitbook.io/docs/)
- [Launch documentation](https://docs.adobelaunch.com/)
- [Launch extension developer docs](https://developer.adobelaunch.com/extensions/)
- [Launch developers slack channel](http://join.launchdevelopers.chat/)