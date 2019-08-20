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
#include "FrequencyStrobeAnimation.h"

void FrequencyStrobeAnimation::animate() {
    calculateBright("FrequencyStrobeAnimation");
    uint8_t mode = getOption("FrequencyStrobeAnimation.mode", 0);

    switch (mode) {
        case 1:
            if (flashes[2]) drawHighs();
            else drawSilence();
            break;
        case 2:
            if (flashes[1]) drawMids();
            else drawSilence();
            break;
        case 3:
            if (flashes[0]) drawMids();
            else drawSilence();
            break;
        case 0:
        default:
            if (flashes[2]) drawHighs();
            else if (flashes[1]) drawMids();
            else if (flashes[0]) drawLows();
            else drawSilence();
            break;
    }

    FastLED.show();
}

void FrequencyStrobeAnimation::drawHighs() {
    auto led = Application::getInstance().getLed();
    for (int i = 0; i < LED_LENGTH; i++) {
        led->setColorAt(i, CHSV(getHighColor(), getHighSaturation(), mapBright(bright[2])));
    }
}

void FrequencyStrobeAnimation::drawMids() {
    auto led = Application::getInstance().getLed();
    for (int i = 0; i < LED_LENGTH; i++) {
        led->setColorAt(i, CHSV(getMidColor(), getMidSaturation(), mapBright(bright[1])));
    }
}

void FrequencyStrobeAnimation::drawLows() {
    auto led = Application::getInstance().getLed();
    for (int i = 0; i < LED_LENGTH; i++) {
        led->setColorAt(i, CHSV(getLowColor(), getLowSaturation(), mapBright(bright[0])));
    }
}

void FrequencyStrobeAnimation::drawSilence() {
    auto led = Application::getInstance().getLed();
    for (int i = 0; i < LED_LENGTH; i++) {
        led->setColorAt(i, CHSV(getEmptyColor(), getEmptySaturation(), getMinimalBright()));
    }
}
