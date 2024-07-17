#pragma once

#ifdef ESP32
#include <HTTPClient.h>
#endif
#ifdef ESP8266
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#endif
#include "AnimateStatsPlugin.h"

class DemoModePlugin : public AnimateStatsPlugin
{
private:
  unsigned long lastUpdate = 0;
  int connectionRetries = 0;
  bool connected = false;
  bool connectedInternet = false;
  int randomCalls = 0;
  int randomFax = 0;
  int randomSms = 0;

  
  void checkForInternet();
  int generateRandomNumber();



  HTTPClient http;

public:
  void update();
  void setup() override;
  void loop() override;
  const char *getName() const override;

};
