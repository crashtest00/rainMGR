#include "NextRun.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoHttpClient.h>

NextRun::NextRun(String domain, int srvPort) {
    host = domain;
    port = srvPort;
}

int NextRun::delayUntil() {
    HTTPClient http;

    // Make the HTTP GET request to fetch the time difference in seconds
    if (http.begin(host + ":" + port + "/api/nextrun")) {
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