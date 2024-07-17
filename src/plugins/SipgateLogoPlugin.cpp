#include "plugins/SipgateLogoPlugin.h"
#include "canvas.h"

#ifdef ESP8266
WiFiClient wiFiClient;
#endif


void SipgateLogoPlugin::setup() {
    Screen.clear();
}

void SipgateLogoPlugin::loop() {
    Canvas.bootAnimation();
}

const char *SipgateLogoPlugin::getName() const {
    return "Sipgate Logo";
}
