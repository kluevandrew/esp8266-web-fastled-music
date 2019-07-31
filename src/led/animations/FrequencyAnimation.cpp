//
// Created by Андрей Клюев on 2019-07-31.
//

#include <Application.h>
#include "FrequencyAnimation.h"


FrequencyAnimation::FrequencyAnimation(const JsonObject& options) {
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
        averageLevels[i] = levels[i] * averageCoefficient + averageLevels[i] * (1 - averageCoefficient);  // global filter
        levels[i] = newLevels[i] * smoothFrequency + levels[i] * (1 - smoothFrequency); // local filter

        if (levels[i] > ((float)averageLevels[i] * maxFrequencyCoefficient)) {
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