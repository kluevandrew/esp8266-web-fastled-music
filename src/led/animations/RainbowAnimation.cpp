//
// Created by Андрей Клюев on 2019-08-01.
//

#include "RainbowAnimation.h"
#include <Application.h>

RainbowAnimation::RainbowAnimation(const JsonObject &options) {
    if (options.containsKey("step")) {
        step = options["step"];
    }

    if (options.containsKey("period")) {
        period = options["period"];
    }

    if (options.containsKey("speed")) {
        speed = options["speed"];
    }
}

void RainbowAnimation::animate() {
    auto led = Application::getInstance().getLed();

    if (millis() - timer > speed) {
        timer = millis();
        color += period;
        if (color > 255) {
            color = 0;
        }
        if (color < 0) {
            color = 255;
        }
    }
    steps = color;
    for (int i = 0; i < LED_LENGTH; i++) {
        led->setColorAt(i, CHSV((int)floor(steps), 255, 255));
        steps += step;
        if (steps > 255) {
            steps = 0;
        }
        if (steps < 0) {
            steps = 255;
        }
    }

    FastLED.show();
}
