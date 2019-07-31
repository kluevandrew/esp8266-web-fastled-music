//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_LEDANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_LEDANIMATION_H
#include "ArduinoJson.h"

class LedAnimation {
public:
    explicit LedAnimation() = default;
    virtual ~LedAnimation() = default;
    virtual void animate() = 0;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_LEDANIMATION_H
