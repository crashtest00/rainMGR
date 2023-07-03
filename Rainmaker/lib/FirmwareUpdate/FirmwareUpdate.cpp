#include "FirmwareUpdate.h"
#include <ArduinoJson.h>
#include <WiFiClient.h>

FirmwareUpdate::FirmwareUpdate() {
  SPIFFS.begin();
}

void FirmwareUpdate::update(float localVersion) {
  if (isUpdateAvailable(localVersion)) {
    WiFiClient client;
    httpUpdate.rebootOnUpdate(false);

    Serial.print(F("Retrieving new firmware from "));
    Serial.println(firmwarePath);

    t_httpUpdate_return ret = httpUpdate.update(client, "192.168.1.168", 3000, firmwarePath);

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        delay(1000); // Wait a second and restart
        ESP.restart();
        break;
    }
  } else {
    Serial.println("No firmware update available");
  }
}

bool FirmwareUpdate::isUpdateAvailable(float localVersion) {
  HTTPClient http;

  int retryCount = 0;
  const int maxRetryCount = 3;
  bool requestSuccessful = false;

  while (retryCount < maxRetryCount && !requestSuccessful) {
    // Connect to the server
    if (http.begin("http://192.168.1.168:3000/api/getUpdate")) {
      // Make the HTTP GET request
      int httpResponseCode = http.GET();

      // Check if the request was successful
      if (httpResponseCode == HTTP_CODE_OK) {
        String response = http.getString();
        http.end();
        requestSuccessful = true;
        Serial.print("Update check successful! Attempts made: ");
        Serial.println(retryCount+1);

        // Handle JSON response
        DynamicJsonDocument responseDoc(1024);
        DeserializationError responseError = deserializeJson(responseDoc, response);

        if (responseError) {
          Serial.println(F("Failed to parse update response"));
          Serial.println(response);
          return false;
        }

        // Parse JSON response
        float remoteVersion = responseDoc["version"];
        String remoteCreatedDate = responseDoc["created_date"];
        firmwarePath = "/"+responseDoc["firmware_path"].as<String>();

        if (remoteVersion > localVersion) {
          Serial.println(F("Firmware update available"));
          Serial.print(F("Remote Version: "));
          Serial.println(remoteVersion);
          Serial.print(F("Remote Created Date: "));
          Serial.println(remoteCreatedDate);
          return true;
        } else {
          Serial.println(F("Firmware up to date"));
          Serial.print("Remote Version: ");
          Serial.println(remoteVersion);
          Serial.print(F("Local Version: "));
          Serial.println(localVersion);
          return false;
        }
      } else {
        Serial.println(F("Failed to send update request"));
        Serial.print("HTTP response code: ");
        Serial.println(httpResponseCode);
        http.end();
        return false;
      }
    } else {
      Serial.println(F("Failed to connect to update server"));
      return false;
    }
    if (!requestSuccessful) {
      Serial.print("Attempts made: ");
      Serial.println(retryCount+1);
    }
  }
  Serial.print("Unhandled exception! Could not check for update.");
  return false;
}

