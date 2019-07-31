//
// Created by Андрей Клюев on 2019-07-31.
//

#include "Led.h"
#include <config/config.h>

Led::Led() {
    FastLED.addLeds<WS2813, LED_DATA_PIN, GRB>(strip, LED_LENGTH);
    if (FASTLED_POWER_LIMIT > 0) {
        FastLED.setMaxPowerInVoltsAndMilliamps(5, FASTLED_POWER_LIMIT);
    }
    FastLED.showColor(CRGB::Black);
    FastLED.setBrightness(LED_DEFAULT_BRIGHTNESS);
}

void Led::animate() {
    this->animation->animate();
}

void Led::setColorAt(int index, const CRGB& color) {
    strip[index] = color;
}

CRGB Led::getColorAt(int index) {
    return strip[index];
}

LedAnimation *Led::getAnimation() const {
    return animation;
}

void Led::setAnimation(LedAnimation *newAnimation) {
    FastLED.showColor(CRGB::Black);
    delete this->animation;
    this->animation = newAnimation;
}

