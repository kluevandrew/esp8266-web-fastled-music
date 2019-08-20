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
#include "SimpleFrequencyAnimation.h"
#include <Application.h>

void SimpleFrequencyAnimation::animate() {
    auto led = Application::getInstance().getLed();
    calculateBright();

    uint8_t direction = getOption("direction", 0);
    if (direction == 1) {
        for (int i = 0; i < LED_LENGTH; i++) {
            if (i < LED_LENGTH / 3) {
                led->setColorAt(i, CHSV(getLowColor(), getLowSaturation(), mapBright(bright[2])));
            } else if (i < LED_LENGTH * 2 / 3) {
                led->setColorAt(i, CHSV(getMidColor(), getMidSaturation(), mapBright(bright[1])));
            } else if (i < LED_LENGTH) {
                led->setColorAt(i, CHSV(getHighColor(), getHighSaturation(), mapBright(bright[0])));
            }
        }
    } else if (direction == 2) {
        auto part = ceil(LED_LENGTH / 5.0);
        for (int i = 0; i < LED_LENGTH; i++) {
            if (i < part) {
                led->setColorAt(i, CHSV(getHighColor(), getHighSaturation(), mapBright(bright[2])));
            } else if (i < part * 2) {
                led->setColorAt(i, CHSV(getMidColor(), getMidSaturation(), mapBright(bright[1])));
            } else if (i < part * 3) {
                led->setColorAt(i, CHSV(getLowColor(), getLowSaturation(), mapBright(bright[0])));
            } else if (i < part * 4) {
                led->setColorAt(i, CHSV(getMidColor(), getMidSaturation(), mapBright(bright[1])));
            } else if (i < LED_LENGTH) {
                led->setColorAt(i, CHSV(getHighColor(), getHighSaturation(), mapBright(bright[2])));
            }
        }
    } else {
        for (int i = 0; i < LED_LENGTH; i++) {
            if (i < LED_LENGTH / 3) {
                led->setColorAt(i, CHSV(getHighColor(), getHighSaturation(), mapBright(bright[2])));
            } else if (i < LED_LENGTH * 2 / 3) {
                led->setColorAt(i, CHSV(getMidColor(), getMidSaturation(), mapBright(bright[1])));
            } else if (i < LED_LENGTH) {
                led->setColorAt(i, CHSV(getLowColor(), getLowSaturation(), mapBright(bright[0])));
            }
        }
    }

    FastLED.show();
}