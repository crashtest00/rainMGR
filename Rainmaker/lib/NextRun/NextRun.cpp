#include "NextRun.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoHttpClient.h>

NextRun::NextRun() {}

int NextRun::delayUntil() {
    HTTPClient http;

    // Make the HTTP GET request to fetch the time difference in seconds
    if (http.begin("http://192.168.1.90:3000/api/nextrun")) {
        int httpResponseCode = http.GET();

        if (httpResponseCode == HTTP_CODE_OK) {
            String response = http.getString();
            http.end();

            // Parse the time difference from the response
            int timeDifference = response.toInt();

            // Return the time difference in seconds
            return timeDifference;
        } else {
            Serial.print("HTTP GET request failed, error code: ");
            Serial.println(httpResponseCode);
            http.end();
            return 0; // Return an error value or handle the error accordingly
        }
    } else {
        Serial.println(F("Failed to connect to the server"));
        return 0; // Return an error value or handle the error accordingly
    }
}

// Private function to get the timings from the server
String NextRun::getDelay() {

    // Create the request URL
    String url = "http://192.168.1.168:3000/api/nextrun";

    // Make the HTTP request to fetch the JSON list
    HTTPClient http;
    http.begin(url);

    int httpResponseCode = http.GET();
    if (httpResponseCode == HTTP_CODE_OK) {
        String jsonResponse = http.getString();
        return jsonResponse;
    } else {
        Serial.print("HTTP GET request failed, error code: ");
        Serial.println(httpResponseCode);
    }

    http.end();
    return "";
}