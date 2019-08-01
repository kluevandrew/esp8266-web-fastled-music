//
// Created by Андрей Клюев on 2019-08-01.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_DYNAMICCOLORANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_DYNAMICCOLORANIMATION_H

#include "LedAnimation.h"
#include <FastLED.h>

class DynamicColorAnimation: public LedAnimation {
public:
    DynamicColorAnimation() = default;

    explicit DynamicColorAnimation(const JsonObject &options);

    ~DynamicColorAnimation() override = default;

    void animate() override;

private:
    uint8_t color = 0;
    uint8_t saturation = 255;
    uint8_t bright = 255;
    uint8_t speed = 100;
    unsigned long timer = 0;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_DYNAMICCOLORANIMATION_H
