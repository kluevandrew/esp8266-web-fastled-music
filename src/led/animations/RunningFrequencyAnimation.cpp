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
        speed = options["speed"];
    }
}

void RunningFrequencyAnimation::animate() {
    auto led = Application::getInstance().getLed();
    calculateBright();

    led->setColorAt(LED_LENGTH / 2, CHSV(emptyColor, 255, minimalBright));
    int countOfVariants = 0;
    countOfVariants += (int)running[0];
    countOfVariants += (int)running[1];
    countOfVariants += (int)running[2];
    double maximum = max(levels[0], max(levels[1], levels[2]));

    if (running[0] || running[1] || running[2]) {
        switch (mode) {
            case 0:
                if (countOfVariants > 1) {
                    running[0] = maximum == levels[0];
                    running[1] = maximum == levels[1];
                    running[2] = maximum == levels[2];
                }
                if (running[0]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(lowColor, 255, bright[0]));
                } else if (running[1]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(midColor, 255, bright[1]));
                } else if (running[2]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(highColor, 255, bright[2]));
                }
                break;
            case 1:
                if (running[2]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(highColor, 255, bright[2]));
                }
                break;
            case 2:
                if (running[1]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(midColor, 255, bright[1]));
                }
                break;
            case 3:
                if (running[0]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(lowColor, 255, bright[0]));
                }
                break;
        }
    }


    led->setColorAt((LED_LENGTH / 2) - 1, led->getColorAt(LED_LENGTH / 2));
    if (millis() - stepTimer > speed) {
        stepTimer = millis();
        for (int i = 0; i < LED_LENGTH / 2 - 1; i++) {
            led->setColorAt(i, led->getColorAt(i + 1));
            led->setColorAt(LED_LENGTH - i - 1, led->getColorAt(i));
        }
    }

    FastLED.show();
}
