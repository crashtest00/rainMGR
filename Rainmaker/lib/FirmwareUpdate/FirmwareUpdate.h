#ifndef FirmwareUpdate_h
#define FirmwareUpdate_h

#include <Arduino.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <SPIFFS.h>

class FirmwareUpdate {
public:
  FirmwareUpdate();
  void update(float);


private:
  String firmwarePath;
  String filesystemPath;
  bool isUpdateAvailable(float);
};

#endif