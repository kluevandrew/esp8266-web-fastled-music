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
#include "MusicAnimation.h"

void MusicAnimation::calculateBright(const String& animationName) {
    int smoothStep = getOption((animationName + ".smoothStep").c_str(), 20);
    uint8_t minimalBright = getOption((animationName + ".minimalBright").c_str(), 30);
    double smoothFrequency = getOption((animationName + ".smoothFrequency").c_str(), 0.8);
    double maxFrequencyCoefficient = getOption((animationName + ".maxFrequencyCoefficient").c_str(), 1.2);
    double averageCoefficient = getOption((animationName + ".averageCoefficient").c_str(), 0.006);

    auto audioAnalyzer = Application::getInstance().getAudioAnalyzer();
    audioAnalyzer->analyzeFrequency();

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