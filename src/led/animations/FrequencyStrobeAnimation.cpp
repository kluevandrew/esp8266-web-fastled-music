//
// Created by Андрей Клюев on 2019-08-01.
//

#include "FrequencyStrobeAnimation.h"
#include <Application.h>

FrequencyStrobeAnimation::FrequencyStrobeAnimation(const JsonObject &options) : FrequencyAnimation(options) {
    if (options.containsKey("emptyColor")) {
        emptyColor = options["emptyColor"];
    }

    if (options.containsKey("mode")) {
        mode = options["mode"];
    }
}

void FrequencyStrobeAnimation::animate() {
    calculateBright();
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
        led->setColorAt(i, CHSV(highColor, 255, bright[2]));
    }
}
void FrequencyStrobeAnimation::drawMids() {
    auto led = Application::getInstance().getLed();
    for (int i = 0; i < LED_LENGTH; i++) {
        led->setColorAt(i, CHSV(midColor, 255, bright[1]));
    }
}
void FrequencyStrobeAnimation::drawLows() {
    auto led = Application::getInstance().getLed();
    for (int i = 0; i < LED_LENGTH; i++) {
        led->setColorAt(i, CHSV(lowColor, 255, bright[0]));
    }
}
void FrequencyStrobeAnimation::drawSilence() {
    auto led = Application::getInstance().getLed();
    for (int i = 0; i < LED_LENGTH; i++) {
        led->setColorAt(i, CHSV(emptyColor, 255, minimalBright));
    }
}
