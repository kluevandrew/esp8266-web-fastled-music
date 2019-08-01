//
// Created by Андрей Клюев on 2019-08-01.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_DIRECTCOLORANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_DIRECTCOLORANIMATION_H


#include "LedAnimation.h"
#include <FastLED.h>

class DirectColorAnimation : public LedAnimation {
public:
    DirectColorAnimation() = default;

    explicit DirectColorAnimation(const JsonObject &options);

    ~DirectColorAnimation() override = default;

    void animate() override;

private:
    uint8_t color = 0;
    uint8_t saturation = 0;
    uint8_t bright = 255;
    bool done = false;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_DIRECTCOLORANIMATION_H
