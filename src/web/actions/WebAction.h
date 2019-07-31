//
// Created by Андрей Клюев on 2019-07-30.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_WEBACTION_H
#define ESP8266_WEB_FASTLED_MUSIC_WEBACTION_H


#include <ESPAsyncWebServer.h>
#include "ArduinoJson.h"

class WebAction {
public:
    virtual void operator () (AsyncWebServerRequest *request);
    virtual void operator () (AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
protected:
    static void json(AsyncWebServerRequest *request, const DynamicJsonDocument& response);
    static void json(AsyncWebServerRequest *request, const DynamicJsonDocument& response, int code);
    static void jsonBadRequest(AsyncWebServerRequest *request);
};


#endif //ESP8266_WEB_FASTLED_MUSIC_WEBACTION_H
