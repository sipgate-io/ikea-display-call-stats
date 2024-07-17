#pragma once

#ifdef ESP32
#include <HTTPClient.h>
#endif
#ifdef ESP8266
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#endif
#include "PluginManager.h"

class SipgateLogoPlugin : public Plugin
{
public:
  void setup() override;
  void loop() override;
  const char *getName() const override;

};
