//
// Created by Андрей Клюев on 2019-07-31.
//

#include "NoopAnimation.h"

void NoopAnimation::animate() {
    FastLED.showColor(CRGB::Black);
}
