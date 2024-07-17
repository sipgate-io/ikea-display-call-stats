#include "plugins/CallStatsPlugin.h"
#include "canvas.h"

// https://github.com/chubin/wttr.in/blob/master/share/translations/en.txt
#ifdef ESP8266
WiFiClient wiFiClient;
#endif



void CallStatsPlugin::checkForInternet(){
    String callStatsApiString = "http://sipgate.de/"; // not using https cuz ssl need more config
    #ifdef ESP32
        http.begin(callStatsApiString);
    #endif
    #ifdef ESP8266
        http.begin(wiFiClient, callStatsApiString);
    #endif

        int code = http.GET();
        Serial.println(code);
        if (code == HTTP_CODE_MOVED_PERMANENTLY) // can't get an 301 without internet 5head
        {
            Serial.println("Internet connection established");
            this->connectedInternet = true;
        }
        else{
            Serial.println("No internet connection");

        }

}



void CallStatsPlugin::setup()
{
    // loading screen
    Screen.clear();

    currentStatus = LOADING;
    Canvas.bootAnimation();

    this->checkForInternet();
    this->lastUpdate = millis();
    if (connectedInternet)
        {
            this->update();
        }
    currentStatus = NONE;
}

void CallStatsPlugin::loop()
{
    if(!connectedInternet){
        this->checkForInternet();
        Canvas.displayError(3, 100);
        return;
    }
    if(!connected){
        Canvas.displayError(3, 100);
    }
    if (millis() >= this->lastUpdate + (1000 * 5)) // call update every 5 secs
    {

        this->update();
        this->lastUpdate = millis();
        Serial.println("updating call Stats");
    };
}

void CallStatsPlugin::update()
{
    Serial.println("Called Update");
    String start = "https://";
    String mid = CALL_STATS_SERVER;
    String end = "/stats";
    String callStatsApiString = start + mid + end; // weird hack to force c to use String instead of char[], format not available in this version
    #ifdef ESP32
        http.begin(callStatsApiString);
    #endif
    #ifdef ESP8266
        http.begin(wiFiClient, callStatsApiString);
    #endif
        http.addHeader("Accept", "application/json");

        int code = http.GET();
        Serial.println("HTTP code");
        Serial.println(code);
        if (code == HTTP_CODE_OK) 
        {
            this->connectionRetries = 0;
            this->connected = true;
            DynamicJsonDocument doc(2048);
            deserializeJson(doc, http.getString());
            // std::vector<int> hh = {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10};
            std::string calls = doc["callCount"].as<std::string>();
            std::string fax = doc["faxCount"].as<std::string>();
            std::string sms = doc["smsCount"].as<std::string>();

            std::string text = "Calls: " + calls + " SMS: " + sms + " Fax: " + fax;

            Screen.scrollText(text, 60);
        }
        else{
            if(code == -5){ // HTTP -5 denotes unstable connection TODO: fix, for now this stabilizes things
                this->connectionRetries++;

                if(connectionRetries < 5)
                {
                    return;
                }
            }
            connected = false;
        }
}

const char *CallStatsPlugin::getName() const
{
    return "CallStats";
}
