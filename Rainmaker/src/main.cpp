/* 
VERSION 0.3
*/

#include <Arduino.h>
#include "WiFiConnection.h"
#include "ZoneTimings.h"
#include "FirmwareUpdate.h"

RTC_DATA_ATTR int rtcPersist = 0; // Prototype for storing information in persistant RTC mem
float VERSION = 0.3;

// Note: Setup runs on every wake!!
void setup() {
  Serial.begin(115200);
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  // Connect to wifi
  WiFiConnection wifiConnect;
  wifiConnect.init();
  wifiConnect.connect();

  // Check for updates
  FirmwareUpdate checkForUpdates;
  checkForUpdates.update(VERSION);

}

// Used for bench testing. Move to main when it works
void loop() {  
  WiFiConnection connectionCheck;
  time_t currentTime = time(nullptr);
  Serial.print("ESP is running! Current time is: ");
  Serial.println(currentTime);
  Serial.print("Wifi connected: ");
  Serial.println(connectionCheck.isConnected());
  delay(1500);

  ZoneTimings runZones;
  runZones.runZones();
}