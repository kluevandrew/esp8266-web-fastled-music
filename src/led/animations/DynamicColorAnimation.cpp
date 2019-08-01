//
// Created by Андрей Клюев on 2019-08-01.
//

#include "DynamicColorAnimation.h"

DynamicColorAnimation::DynamicColorAnimation(const JsonObject &options) {
    if (options.containsKey("saturation")) {
        saturation = options["saturation"];
    }

    if (options.containsKey("bright")) {
        bright = options["bright"];
    }

    if (options.containsKey("speed")) {
        speed = options["speed"];
    }
}

void DynamicColorAnimation::animate() {
    if (millis() - timer > speed) {
        timer = millis();
        if (++color > 255) {
            color = 0;
        }
    }
    FastLED.showColor(CHSV(color, saturation, bright));
}