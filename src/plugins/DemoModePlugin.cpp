#include "plugins/DemoModePlugin.h"
#include <random>
#include <string>

// https://github.com/chubin/wttr.in/blob/master/share/translations/en.txt
#ifdef ESP8266
WiFiClient wiFiClient;
#endif

void DemoModePlugin::setup()
{
    // loading screen
    Screen.clear();

    this->currentStat = StatType::CALL;
    this->calls = std::to_string(generateRandomNumber());
    this->fax = std::to_string(generateRandomNumber());
    this->sms = std::to_string(generateRandomNumber());

}

int DemoModePlugin::generateRandomNumber() {
    static std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1500);
    return dis(gen);
}

void DemoModePlugin::loop()
{
    
    if (millis() >= this->lastStatsSwitch + STATS_SWITCH_INTERVAL)
    {
        if (static_cast<int>(this->currentStat) == 0) {
            Screen.clear();
            Screen.scrollText("Demo Mode");
        }
        this->lastStatsSwitch = millis();
        this->currentStat = static_cast<StatType>((static_cast<int>(this->currentStat) + 1) % 3);
        this->displayCurrentStat();
    }

}


const char *DemoModePlugin::getName() const
{
    return "Demo Mode";
}
