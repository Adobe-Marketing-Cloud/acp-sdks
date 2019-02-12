# ACPWeatherExample
The ACPWeatherExample project is a simple demonstration of how you can write your own custom extension to integrate with the ACP SDK.

<hr>

## Getting Started

1. Download or clone the [weather-example branch](https://github.com/Adobe-Marketing-Cloud/acp-sdks/tree/weather-example)
2. Navigate to the `ACPWeatherExample` directory in terminal and run `pod update`
3. Open `ACPWeatherExample.xcworkspace`
4. The `ACPWeatherExample` project has two targets in it:
  - `ACPWeatherExample` - a target to produce a static library output
  - `TestApp` - a simple app used for testing the `ACPWeatherExample` extension with the SDK
5. If you want to run the test app, do the following:
  - Go to https://openweathermap.org/ and generate an API key
  - In `AppDelegate.m` for the `TestApp`, fill in the value of `ACPWeatherExampleApiKey` with your API key
  - Select the `TestApp` scheme and press `Run`

## Extension Documentation

[View the SDK Documentation](https://aep-sdks.gitbook.io/docs/) for information on how to build your own extension.
