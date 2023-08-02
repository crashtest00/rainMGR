/* 
VERSION 0.5
*/

#include <Arduino.h>
#include "WiFiConnection.h"
#include "ZoneTimings.h"
#include "FirmwareUpdate.h"
#include "NextRun.h"

#define uS_TO_S_FACTOR 1000000  
RTC_DATA_ATTR int rtcPersist = 0; // Prototype for storing information in persistant RTC mem

float VERSION = 0.5;
String domain = "http://rainmaker.home";
int port = 3000;

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
  FirmwareUpdate checkForUpdates(domain, port);
  checkForUpdates.update(VERSION);

    WiFiConnection connectionCheck;
  time_t currentTime = time(nullptr);
  Serial.print("ESP is running! Current time is: ");
  Serial.println(currentTime);
  Serial.print("Wifi connected: ");
  Serial.println(connectionCheck.isConnected());

  // Run irrigation for zones
  Serial.println("Running zones");
  ZoneTimings runZones(domain, port);
  runZones.runZones();
  NextRun nextRun(domain, port);
  
  u64_t deepSleep = nextRun.delayUntil();
  // u64_t deepSleep = 2148; // 32 vs 64 bit testing. 32 bit overflows at 2148 and higher.
  Serial.print("Next run in ");
  Serial.print(deepSleep * uS_TO_S_FACTOR);
  Serial.println(" microseconds");
  esp_sleep_enable_timer_wakeup(deepSleep * uS_TO_S_FACTOR);
  Serial.flush();
  delay(1000);
  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {}