/* 
VERSION 0.1
- 4 Zones
- OTA Updates
- Fixed run time (TODO: Get this from server)
- Fixed Schedule (TODO: Get this from server daily)
*/

#include <Arduino.h>
#include "zones.h"

RTC_DATA_ATTR int rtcPersist = 0; // Prototype for storing information in persistant RTC mem

// Set controller ID
const char* id = "MANIFOLD_1";

// Define the number of zones
const int numZones = 4;

// Assign GPIO pins for turning zones on
const int zoneOn[numZones] = {32, 33, 25, 26};  // Example: Pins to turn zones on

// Assign GPIO pins for turning zones off
const int zoneOff[numZones] = {21, 19, 18, 5};  // Example: Pins to turn zones off

// Time required to activate solenoid (ms)
const int solWait = 250;

// Set duration for each zone (Needs moved to setup() when set buy cloud)
const int durations[numZones] = {3000, 3000, 3000, 3000};

// Note: Setup runs on every wake!!
void setup() {
  Serial.begin(115200);
  // Set the pin modes
  for (int i = 0; i < numZones; i++) {
    Serial.print("Setting ON pin mode on pin " + String(zoneOn[i]));
    pinMode(zoneOn[i], OUTPUT);
    Serial.print("Setting OFF pin mode on pin " + String(zoneOff[i]));
    pinMode(zoneOff[i], OUTPUT);
  }
}

// Used for bench testing
void loop() {
  for (int i = 0; i < numZones; i++) {
    // Activate sprinkler in zone[i]
    Serial.println("Turning on Zone " + String(i) + " with Pin " + String(zoneOn[i]));
    digitalWrite(zoneOn[i], HIGH);
    delay(solWait);
    digitalWrite(zoneOn[i], LOW);

    // Run for duration
    delay(durations[i]);

    // Shut off the current zone 
    Serial.println("Turning off Zone " + String(i) + " with Pin " + String(zoneOff[i]));
    digitalWrite(zoneOff[i], HIGH);
    delay(solWait);
    digitalWrite(zoneOff[i], LOW);

    // Pause before next zone:
    delay(solWait);
  }    
}