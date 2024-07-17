#include "plugins/AnimateStatsPlugin.h"
#include "canvas.h"

// https://github.com/chubin/wttr.in/blob/master/share/translations/en.txt
#ifdef ESP8266
WiFiClient wiFiClient;
#endif




void AnimateStatsPlugin::checkForInternet(){

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



void AnimateStatsPlugin::setup()
{
    // loading screen
    Canvas.clear();

    currentStatus = LOADING;
    //Canvas.bootAnimation();

    this->lastMatrix = Canvas.emptyImage();

    this->checkForInternet();
    this->lastFetch = millis();
    if (connectedInternet)
        {
            this->fetchData();
        }
    currentStatus = NONE;
}

void AnimateStatsPlugin::loop()
{
    if(!connectedInternet){
        this->checkForInternet();
        Canvas.displayError(3, 100);
        return;
    }
    if(!connected){
        Canvas.displayError(3, 100);
    }
    if (millis() >= this->lastFetch + FETCH_INTERVAL)
    {
        this->fetchData();
        this->lastFetch = millis();
        Serial.println("updated call Stats");
        
    }
    if (millis() >= this->lastStatsSwitch + STATS_SWITCH_INTERVAL)
    {
        this->lastStatsSwitch = millis();
        this->currentStat = static_cast<StatType>((static_cast<int>(this->currentStat) + 1) % 3);
        this->displayCurrentStat();
    }
}

void AnimateStatsPlugin::displayCurrentStat() {
    Canvas.clear();
    
    auto callMatrix = createCallMatrix();
    auto faxMatrix = createFaxMatrix();
    auto smsMatrix = createSmsMatrix();
    std::vector<std::vector<short>> animationFrame;

    switch(this->currentStat) {
        case StatType::CALL:
            animationFrame = Canvas.horizontalConcat(lastMatrix, callMatrix);
            Canvas.horizontalWipeAnimation(animationFrame, 50);
            lastMatrix = callMatrix;
            // Canvas.drawImage();
            break;
        case StatType::FAX:
            animationFrame = Canvas.horizontalConcat(lastMatrix, faxMatrix);
            Canvas.horizontalWipeAnimation(animationFrame, 50);
            lastMatrix = faxMatrix;
            break;
        case StatType::SMS:
            animationFrame = Canvas.horizontalConcat(lastMatrix, smsMatrix);
            Canvas.horizontalWipeAnimation(animationFrame, 50);
            lastMatrix = smsMatrix;
            break;
    }
}

std::vector<std::vector<short>>  AnimateStatsPlugin::createCallMatrix()
{
    auto padding1x1 = Canvas.emptyImage(0, 1, 1);
    // move callIcon by 1 to the right and 1 down
    auto paddedImage = Canvas.verticalConcat(padding1x1, Canvas.callIcon);
    paddedImage = Canvas.horizontalConcat(padding1x1, paddedImage);
    // Move stats down by 1
    paddedImage = Canvas.verticalConcat(paddedImage, padding1x1);
    auto numberPixels = Canvas.stringToPixelMatrix(aggregate_numbers(this->calls));
    paddedImage = Canvas.verticalConcat(paddedImage, numberPixels);
    // padding to 16x16 matrix
    paddedImage = Canvas.horizontalConcat(paddedImage, padding1x1);
    paddedImage = Canvas.verticalConcat(paddedImage, padding1x1);
    return paddedImage;
}

std::vector<std::vector<short>>  AnimateStatsPlugin::createFaxMatrix()
{
    auto padding1x1 = Canvas.emptyImage(0, 1, 1);
    // move callIcon by 1 to the right and 1 down
    auto paddedImage = Canvas.stringToPixelMatrix("FA"); 
    paddedImage = Canvas.horizontalConcat(paddedImage, padding1x1);
    paddedImage = Canvas.horizontalConcat(paddedImage, Canvas.stringToPixelMatrix("X"));
    Serial.println(pixelMatrixToString(paddedImage));
    // Move stats down by 1
    paddedImage = Canvas.verticalConcat(paddedImage, padding1x1);
    auto numberPixels = Canvas.stringToPixelMatrix(aggregate_numbers(this->fax));
    paddedImage = Canvas.verticalConcat(paddedImage, numberPixels);
    // padding to 16x16 matrix
    paddedImage = Canvas.horizontalConcat(paddedImage, padding1x1);
    paddedImage = Canvas.verticalConcat(paddedImage, padding1x1);
    return paddedImage;
}

  std::vector<std::vector<short>> AnimateStatsPlugin::createSmsMatrix()
  {
    auto padding1x1 = Canvas.emptyImage(0, 1, 1);
    // Move stats down by 1
    auto paddedImage = Canvas.verticalConcat(Canvas.smsIcon, padding1x1);
    auto numberPixels = Canvas.stringToPixelMatrix(aggregate_numbers(this->sms));
    paddedImage = Canvas.verticalConcat(paddedImage, numberPixels);
    // padding to 16x16 matrix
    paddedImage = Canvas.horizontalConcat(paddedImage, padding1x1);
    paddedImage = Canvas.verticalConcat(paddedImage, padding1x1);
    return paddedImage;
  }


void AnimateStatsPlugin::fetchData()
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
            this->calls = doc["callCount"].as<std::string>();
            this->fax = doc["faxCount"].as<std::string>();
            this->sms = doc["smsCount"].as<std::string>();
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

const char *AnimateStatsPlugin::getName() const
{
    return "StatistikenAnimieren";
}
