//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_ADCACTION_H
#define ESP8266_WEB_FASTLED_MUSIC_ADCACTION_H

#include "WebAction.h"

class AdcAction: public WebAction {
public:
    void operator()(AsyncWebServerRequest *request) override;

};


#endif //ESP8266_WEB_FASTLED_MUSIC_ADCACTION_H
