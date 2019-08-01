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
#include <Application.h>
#include "FrequencyAnimation.h"

FrequencyAnimation::FrequencyAnimation(const JsonObject &options) {
    if (options.containsKey("smoothStep")) {
        smoothStep = options["smoothStep"];
    }

    if (options.containsKey("minimalBright")) {
        minimalBright = options["minimalBright"];
    }

    if (options.containsKey("smoothFrequency")) {
        smoothFrequency = options["smoothFrequency"];
    }

    if (options.containsKey("maxFrequencyCoefficient")) {
        maxFrequencyCoefficient = options["maxFrequencyCoefficient"];
    }

    if (options.containsKey("averageCoefficient")) {
        maxFrequencyCoefficient = options["averageCoefficient"];
    }

    if (options.containsKey("lowColor")) {
        lowColor = options["lowColor"];
    }

    if (options.containsKey("midColor")) {
        midColor = options["midColor"];
    }

    if (options.containsKey("highColor")) {
        highColor = options["highColor"];
    }

}

void FrequencyAnimation::calculateBright() {
    auto audioAnalyzer = Application::getInstance().getAudioAnalyzer();
    audioAnalyzer->analyze();

    double newLevels[3];
    newLevels[0] = audioAnalyzer->getLow();
    newLevels[1] = audioAnalyzer->getMid();
    newLevels[2] = audioAnalyzer->getHigh();
    double newMaxFrequency = audioAnalyzer->getMaxFrequency();

    maxFrequency = newMaxFrequency * averageCoefficient + maxFrequency * (1 - averageCoefficient);
    for (byte i = 0; i < 3; i++) {
        averageLevels[i] =
                levels[i] * averageCoefficient + averageLevels[i] * (1 - averageCoefficient);  // global filter
        levels[i] = newLevels[i] * smoothFrequency + levels[i] * (1 - smoothFrequency); // local filter

        if (levels[i] > ((float) averageLevels[i] * maxFrequencyCoefficient)) {
            bright[i] = 255;
            flashes[i] = true;
            running[i] = true;
        } else {
            flashes[i] = false;
        }

        if (bright[i] >= 0) {
            bright[i] -= smoothStep;
        }

        if (bright[i] < minimalBright) {
            bright[i] = minimalBright;
            running[i] = false;
        }
    }
}