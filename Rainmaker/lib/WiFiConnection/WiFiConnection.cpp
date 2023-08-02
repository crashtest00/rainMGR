#include "WiFiConnection.h"
#include <SPIFFS.h>
#include <ArduinoHttpClient.h>

String ssid;
String password;

WiFiMulti WiFiMulti;

WiFiConnection::WiFiConnection() {}

void WiFiConnection::init(){
  Serial.println("Creating Wifi Connection");
  WiFi.mode(WIFI_STA);
  Serial.println("Loading Credentials");
  // loadCredentials(); // Load SSID and password from file THIS IS BROKEN
  ssid = "";
  password = "";
  WiFiMulti.addAP(ssid, password);
}

void WiFiConnection::connect() {
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print("Tried SSID: ");
    Serial.println(ssid);
    Serial.print("With password: ");
    Serial.println(password);
    delay(100);
  }
}

bool WiFiConnection::isConnected() {
  return WiFiMulti.run() == WL_CONNECTED;
}

// THIS IS BROKEN
void WiFiConnection::loadCredentials() {
  String s,p;
  File credentialsFile = SPIFFS.open("/credentials.txt", "r");
  if (credentialsFile) {
    s = credentialsFile.readStringUntil('\n');
    // ssid = s.c_str();
    ssid = "whiteRabbit";

    // p = credentialsFile.readStringUntil('\n');
    // password = p.c_str();
    password = "goat3truck4max";
    credentialsFile.close();

    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(password);
  } else {
    Serial.println("NO CREDENTIAL FILE FOUND!");
  }
}
