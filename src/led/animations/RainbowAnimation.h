//
// Created by Андрей Клюев on 2019-08-01.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_RAINBOWANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_RAINBOWANIMATION_H

#include "LedAnimation.h"
#include <FastLED.h>

class RainbowAnimation : public LedAnimation {
public:
    RainbowAnimation() = default;
    explicit RainbowAnimation(const JsonObject& options);
    ~RainbowAnimation() override = default;

    void animate() override;

private:
    unsigned long timer = 0;
    double step = 0.5;
    double steps = 0.0;
    int color = 0;
    int period = 1;
    int speed = 30;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_RAINBOWANIMATION_H
