#include "ZoneTimings.h"
#include "Zone.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <array>

// Constructor requires valid pin pairs for each zone
// Make sure the length of this array matches the header file!
ZoneTimings::ZoneTimings() : zones({
    Zone(32, 21),
    Zone(33, 19),
    Zone(25, 18),
    Zone(26, 4)
}) {
    // Loop through all Zones to set pins to OUTPUT
    // Could improve this by going through "zones" and using the getPins method on each to make sure
    // these stay in sync. Would require refactoring the method to return int instead of string. Oh well.
    int pins[] = {32, 21, 33, 19, 25, 18, 26, 4};
    for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
        Serial.println("Setting pin mode on pin " + String(pins[i]));
        pinMode(pins[i], OUTPUT);
    }
}

void ZoneTimings::runZones() {
    String timingsJSON = getTimings();

    // Parse JSON
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, timingsJSON);

     // Check for parsing errors
    if (error) {
        Serial.print(F("Failed to parse JSON list: "));
        Serial.println(error.c_str());
        return;
    }      

    // iterator to hold the zone idx
    int i = 0;

    // Iterate over each element in the JSON list
    for (JsonVariant element : doc.as<JsonArray>()) {
        // Get duration from JSON
        unsigned int duration = element["duration"];

        // Run irrigation from JSON
        Serial.print(F("Running zone "));
        Serial.print(i+1);
        Serial.print(" on pins ");
        Serial.println(zones[i].pins());

        // Run zone for duration (in seconds)
        runIrrigation(zones[i].on(), zones[i].off(), duration);
        
        //Increment zone number
        i++;
  }
}

// Private function to get the timings from the server
String ZoneTimings::getTimings() {
    // Get the ESP32's MAC Address
    String macAddress = WiFi.macAddress();
    Serial.print("The MAC address for this device is: ");
    Serial.println(macAddress);

    // Create the request URL
    String url = "http://192.168.1.90:3000/api/manifolds";

    // Make the HTTP request to fetch the JSON list
    HTTPClient http;
    http.begin(url);
    http.addHeader("mac-address",macAddress);


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

// Private function to run the irrigation sequence
void ZoneTimings::runIrrigation(int on, int off, unsigned int duration) {
    // Time required to activate solenoid (ms)
    int solCycle = 250;

    // Turn on zone
    Serial.println("Turning on zone");
    digitalWrite(on, HIGH);
    delay(solCycle);
    digitalWrite(on, LOW);
    Serial.println("Zone is running");

    // Wait for duration, assumes seconds
    delay(duration * 1000);

    // Turn off zone
    Serial.println("Turning off zone");
    digitalWrite(off, HIGH);
    delay(solCycle);
    digitalWrite(off, LOW);
    Serial.println("Zone is off");
    delay(1000);
}