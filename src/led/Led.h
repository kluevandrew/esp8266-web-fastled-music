//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_LED_H
#define ESP8266_WEB_FASTLED_MUSIC_LED_H

#include <config/config.h>
#include <FastLED.h>
#include <led/animations/LedAnimation.h>
#include <led/animations/NoopAnimation.h>
#include <led/animations/DirectColorAnimation.h>

class Led {
public:
    explicit Led();

    void animate();

    void setColorAt(int index, const CRGB& color);
    CRGB getColorAt(int index);

    LedAnimation *getAnimation() const;

    void setAnimation(LedAnimation *animation);

private:
    CRGB strip[LED_LENGTH];
    LedAnimation *animation = new DirectColorAnimation();
};


#endif //ESP8266_WEB_FASTLED_MUSIC_LED_H
