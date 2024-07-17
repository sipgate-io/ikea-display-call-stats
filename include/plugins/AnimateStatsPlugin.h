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
#include "secrets.h"
#include "utilities.h"

class AnimateStatsPlugin : public Plugin
{
private:
  static const int FETCH_INTERVAL = 30000;
  unsigned long lastFetch = 0;
  int connectionRetries = 0;
  bool connected = false;
  bool connectedInternet = false;
  
  void checkForInternet();

  HTTPClient http;

protected:
  std::string calls = "-";
  std::string fax = "-";
  std::string sms = "-";
  std::vector<std::vector<short>> lastMatrix;
  enum class StatType { CALL, FAX, SMS };
  StatType currentStat = StatType::CALL;
  static const int STATS_SWITCH_INTERVAL = 5000;
  unsigned long lastStatsSwitch = 0;
  std::vector<std::vector<short>>  createCallMatrix();
  std::vector<std::vector<short>>  createFaxMatrix();
  std::vector<std::vector<short>>  createSmsMatrix();


public:
  void fetchData();
  void setup() override;
  void loop() override;
  void displayCurrentStat();
  const char *getName() const override;

};
