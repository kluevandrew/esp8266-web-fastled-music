//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_STROBEANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_STROBEANIMATION_H


#include "LedAnimation.h"
#include <FastLED.h>

class StrobeAnimation: public LedAnimation {
public:
    explicit StrobeAnimation(const JsonObject& options);
    ~StrobeAnimation() override = default;

    void animate() override;

private:
    int delay = 200;
    CRGB colorOn = CRGB::White;
    CRGB colorOff = CRGB::Black;
    bool state = false;
};

#endif //ESP8266_WEB_FASTLED_MUSIC_STROBEANIMATION_H
