#ifndef FilesystemUpdate_h
#define FilesystemUpdate_h

#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <SPIFFS.h>

class FilesystemUpdate {
public:
  FilesystemUpdate();
  void update();
};

#endif
