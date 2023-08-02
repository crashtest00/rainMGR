#ifndef FirmwareUpdate_h
#define FirmwareUpdate_h

#include <Arduino.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
class FirmwareUpdate {
public:
  FirmwareUpdate(String, int);
  void update(float);


private:
  String host;
  int port;
  String firmwarePath;
  String filesystemPath;
  bool isUpdateAvailable(float);
};

#endif