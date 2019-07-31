//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_ANIMATIONFACTORY_H
#define ESP8266_WEB_FASTLED_MUSIC_ANIMATIONFACTORY_H


#include "ArduinoJson.h"
#include <led/animations/LedAnimation.h>
#include <WString.h>

class AnimationFactory {
public:
    static LedAnimation* create(const String& name);
    static LedAnimation* create(const String& name, const JsonObject& options);
};


#endif //ESP8266_WEB_FASTLED_MUSIC_ANIMATIONFACTORY_H
