#include "filesystemUpdate.h"

FilesystemUpdate::FilesystemUpdate() {
  SPIFFS.begin();
}

void FilesystemUpdate::update() {
  WiFiClient client;
  httpUpdate.rebootOnUpdate(false);

  Serial.println(F("Update start now!"));

  t_httpUpdate_return ret = httpUpdate.updateSpiffs(client, "http://192.168.1.168:3000/filesystem/httpUpdateNewFS.bin");

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      Serial.println(F("Retry in 10secs!"));
      delay(10000); // Wait 10secs
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
}

