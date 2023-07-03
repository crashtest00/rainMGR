#ifndef WiFiConnection_h
#define WiFiConnection_h

#include <WiFi.h>
#include <WiFiMulti.h>

class WiFiConnection {
public:
  WiFiConnection();
  void init();
  void connect();
  bool isConnected();

private:
  void loadCredentials();

  const char* ssid;
  const char* password;
};

#endif
