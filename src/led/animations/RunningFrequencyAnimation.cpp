//
// Created by Андрей Клюев on 2019-08-01.
//

#include "RunningFrequencyAnimation.h"
#include <Application.h>

RunningFrequencyAnimation::RunningFrequencyAnimation(const JsonObject &options) : FrequencyAnimation(options) {
    if (options.containsKey("emptyColor")) {
        emptyColor = options["emptyColor"];
    }

    if (options.containsKey("mode")) {
        mode = options["mode"];
    }

    if (options.containsKey("speed")) {
        mode = options["mode"];
    }
}

void RunningFrequencyAnimation::animate() {
    auto led = Application::getInstance().getLed();
    calculateBright();

    switch (mode) {
        case 0:
            if (running[2]) {
                led->setColorAt(LED_LENGTH / 2, CHSV(highColor, 255, bright[2]));
            } else if (running[1]) {
                led->setColorAt(LED_LENGTH / 2, CHSV(midColor, 255, bright[1]));
            } else if (running[0]) {
                led->setColorAt(LED_LENGTH / 2, CHSV(midColor, 255, bright[0]));
            } else {
                led->setColorAt(LED_LENGTH / 2, CHSV(emptyColor, 255, minimalBright));
            }
            break;
        case 1:
            if (running[2]) {
                led->setColorAt(LED_LENGTH / 2, CHSV(highColor, 255, bright[2]));
            } else {
                led->setColorAt(LED_LENGTH / 2, CHSV(emptyColor, 255, minimalBright));
            }
            break;
        case 2:
            if (running[1]) {
                led->setColorAt(LED_LENGTH / 2, CHSV(midColor, 255, bright[1]));
            } else {
                led->setColorAt(LED_LENGTH / 2, CHSV(emptyColor, 255, minimalBright));
            }
            break;
        case 3:
            if (running[0]) {
                led->setColorAt(LED_LENGTH / 2, CHSV(lowColor, 255, bright[0]));
            } else {
                led->setColorAt(LED_LENGTH / 2, CHSV(emptyColor, 255, minimalBright));
            }
            break;
    }
    led->setColorAt((LED_LENGTH / 2) - 1, led->getColorAt(LED_LENGTH / 2));
    if (millis() - timer > speed) {
        timer = millis();
        for (int i = 0; i < LED_LENGTH / 2 - 1; i++) {
            led->setColorAt(i, led->getColorAt(i + 1));
            led->setColorAt(LED_LENGTH - i - 1, led->getColorAt(i));
        }
    }

    FastLED.show();
}
