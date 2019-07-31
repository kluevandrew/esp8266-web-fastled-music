//
// Created by Андрей Клюев on 2019-07-31.
//

#include "SimpleFrequencyAnimation.h"
#include <Application.h>


SimpleFrequencyAnimation::SimpleFrequencyAnimation(const JsonObject &options) : FrequencyAnimation(options) {
    if (options.containsKey("direction")) {
        direction = String((const char*)options["direction"]);
    }
}

void SimpleFrequencyAnimation::animate() {
    auto led = Application::getInstance().getLed();
    calculateBright();

    if (direction == "rtl") {
        for (int i = 0; i < LED_LENGTH; i++) {
            if (i < LED_LENGTH / 3) {
                led->setColorAt(i, CHSV(lowColor, 255, bright[2]));
            } else if (i < LED_LENGTH * 2 / 3) {
                led->setColorAt(i, CHSV(midColor, 255, bright[1]));
            } else if (i < LED_LENGTH) {
                led->setColorAt(i, CHSV(highColor, 255, bright[0]));
            }
        }
    } else if (direction == "both") {
        auto part = LED_LENGTH / 5;
        for (int i = 0; i < LED_LENGTH; i++) {
            if (i < part) {
                led->setColorAt(i, CHSV(highColor, 255, bright[2]));
            } else if (i < part * 2) {
                led->setColorAt(i, CHSV(midColor, 255, bright[1]));
            } else if (i < part * 3) {
                led->setColorAt(i, CHSV(lowColor, 255, bright[0]));
            } else if (i < part * 4) {
                led->setColorAt(i, CHSV(midColor, 255, bright[1]));
            } else if (i < part * 5) {
                led->setColorAt(i, CHSV(highColor, 255, bright[2]));
            }
        }
    } else {
        for (int i = 0; i < LED_LENGTH; i++) {
            if (i < LED_LENGTH / 3) {
                led->setColorAt(i, CHSV(highColor, 255, bright[2]));
            } else if (i < LED_LENGTH * 2 / 3) {
                led->setColorAt(i, CHSV(midColor, 255, bright[1]));
            } else if (i < LED_LENGTH) {
                led->setColorAt(i, CHSV(lowColor, 255, bright[0]));
            }
        }
    }

    FastLED.show();
}