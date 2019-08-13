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
#ifndef ESP8266_WEB_FASTLED_MUSIC_MUSICANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_MUSICANIMATION_H


#include <Application.h>
#include <led/animations/ConfigurableLedAnimation.hpp>
#include <FastLED.h>

class MusicAnimation : public ConfigurableLedAnimation {
public:
    MusicAnimation() = default;

    explicit MusicAnimation(const JsonObject &options);

    ~MusicAnimation() override = default;

protected:
    int bright[3] = {0, 0, 0};
    boolean flashes[3] = {false, false, false};
    boolean running[3] = {false, false, false};
    double maxFrequency = 0.0;
    double averageLevels[3] = {0.0, 0.0, 0.0};
    double levels[3] = {0.0, 0.0, 0.0};

    void calculateBright(const String &animationName);

    virtual String getName() = 0;

    uint8_t getHighColor() {
        return getOption((getName() + ".highColor.hue").c_str(), (int) HUE_BLUE);
    }

    uint8_t getHighSaturation() {
        return getOption((getName() + ".highColor.sat").c_str(), 255);
    }

    uint8_t getMidColor() {
        return getOption((getName() + ".midColor.hue").c_str(), (int) HUE_GREEN);
    }

    uint8_t getMidSaturation() {
        return getOption((getName() + ".midColor.sat").c_str(), 255);
    }

    uint8_t getLowColor() {
        return getOption((getName() + ".lowColor.hue").c_str(), (int) HUE_RED);
    }

    uint8_t getLowSaturation() {
        return getOption((getName() + ".lowColor.sat").c_str(), 255);
    }

    uint8_t getEmptyColor() {
        return getOption((getName() + ".emptyColor.hue").c_str(), (int) HUE_PURPLE);;
    }

    uint8_t getEmptySaturation() {
        return getOption((getName() + ".emptyColor.sat").c_str(), 255);
    }

    uint8_t getMinimalBright() {
        return getOption((getName() + ".minimalBright").c_str(), 255);
    }
};


#endif //ESP8266_WEB_FASTLED_MUSIC_MUSICANIMATION_H
