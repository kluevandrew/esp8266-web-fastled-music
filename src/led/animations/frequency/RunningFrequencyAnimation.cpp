/*
 * This file is part of the esp8266-web-fastled-music distribution (https://github.com/kluevandrew/esp8266-web-fastled-music).
 * Copyright (c) 2019, Kluev Andrew <kluev.andrew@gmail.com>.
 *
 * esp8266-web-fastled-music is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
 *
 * You are free to:
 *   Share — copy and redistribute the material in any medium or format
 *   Adapt — remix, transform, and build upon the material
 *
 * Under the following terms:
 *   Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
 *   NonCommercial — You may not use the material for commercial purposes.
 *   ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.
 *   No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.
 *
 * For additional information, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
 */
#include "RunningFrequencyAnimation.h"
#include <Application.h>

void RunningFrequencyAnimation::animate() {
    uint8_t mode = getOption("mode", 0);
    unsigned long delay = getOption("delay", 11);

    auto led = Application::getInstance().getLed();
    calculateBright();

    led->setColorAt(LED_LENGTH / 2, CHSV(getEmptyColor(), getEmptySaturation(), getMidSaturation()));
    uint8_t countOfVariants = 0;
    countOfVariants += (uint8_t) running[0];
    countOfVariants += (uint8_t) running[1];
    countOfVariants += (uint8_t) running[2];
    double maximum = max(levels[0], max(levels[1], levels[2]));
    Serial.println(maximum);

    if (running[0] || running[1] || running[2]) {
        switch (mode) {
            case 0:
                if (countOfVariants > 1) {
                    running[0] = maximum == levels[0];
                    running[1] = maximum == levels[1];
                    running[2] = maximum == levels[2];
                }
                if (running[0]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(getLowColor(), getLowColor(), mapBright(bright[0])));
                } else if (running[1]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(getMidColor(), getMidSaturation(), mapBright(bright[1])));
                } else if (running[2]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(getHighColor(), getHighSaturation(), mapBright(bright[2])));
                }
                break;
            case 1:
                if (running[2]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(getHighColor(), getHighSaturation(), mapBright(bright[2])));
                }
                break;
            case 2:
                if (running[1]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(getMidColor(), getMidSaturation(), mapBright(bright[1])));
                }
                break;
            case 3:
                if (running[0]) {
                    led->setColorAt(LED_LENGTH / 2, CHSV(getLowColor(), getLowColor(), mapBright(bright[0])));
                }
                break;
            default:
                led->setColorAt(LED_LENGTH / 2, CRGB::Black);
                break;
        }
    }


    led->setColorAt((LED_LENGTH / 2) - 1, led->getColorAt(LED_LENGTH / 2));
    if (millis() - stepTimer > delay) {
        stepTimer = millis();
        for (int i = 0; i < LED_LENGTH / 2 - 1; i++) {
            led->setColorAt(i, led->getColorAt(i + 1));
            led->setColorAt(LED_LENGTH - i - 1, led->getColorAt(i));
        }
    }

    FastLED.show();
}
