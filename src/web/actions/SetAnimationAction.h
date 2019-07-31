//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_SETANIMATIONACTION_H
#define ESP8266_WEB_FASTLED_MUSIC_SETANIMATIONACTION_H


#include "WebAction.h"

class SetAnimationAction: public WebAction {
public:
    void operator()(AsyncWebServerRequest *request) override {};
    void operator()(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) override;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_SETANIMATIONACTION_H
