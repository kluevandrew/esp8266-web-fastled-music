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
#ifndef ESP8266_WEB_FASTLED_MUSIC_FREQUENCYANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_FREQUENCYANIMATION_H


#include "LedAnimation.h"
#include <FastLED.h>

class FrequencyAnimation : public LedAnimation {
public:
    FrequencyAnimation() = default;

    explicit FrequencyAnimation(const JsonObject &options);

    ~FrequencyAnimation() override = default;

protected:
    int smoothStep = 20;
    byte minimalBright = 30;
    double smoothFrequency = 0.8;
    double maxFrequencyCoefficient = 1.2;
    double averageCoefficient = 0.006;
    uint8_t lowColor = HUE_RED;
    uint8_t midColor = HUE_GREEN;
    uint8_t highColor = HUE_BLUE;

    int bright[3] = {0, 0, 0};
    boolean flashes[3] = {false, false, false};
    boolean running[3] = {false, false, false};
    double maxFrequency = 0.0;
    double averageLevels[3] = {0.0, 0.0, 0.0};
    double levels[3] = {0.0, 0.0, 0.0};

    void calculateBright();
};


#endif //ESP8266_WEB_FASTLED_MUSIC_FREQUENCYANIMATION_H
