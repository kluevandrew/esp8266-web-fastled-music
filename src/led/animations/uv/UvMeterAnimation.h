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
#ifndef ESP8266_WEB_FASTLED_MUSIC_UVMETERANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_UVMETERANIMATION_H


#include <Application.h>
#include "led/animations/MusicAnimation.h"

class UvMeterAnimation : public MusicAnimation {
public:
    UvMeterAnimation() = default;

    ~UvMeterAnimation() override = default;

    void animate() override {};

    void animate(CRGB *strip) override;

    String getName() override {
        return "UvMeter";
    };

private:
    float averageLevel = 50;
    int maxLevel = 100;
    int Rlenght = 0;
    int Llenght = 0;
    float EMPTY_BRIGHT = 30;
    float count;
    float averK = 0.006;
    int MAX_CH = LED_LENGTH / 2;
    float index = (float)255 / MAX_CH;   // коэффициент перевода для палитры
    float MAX_COEF = 1.8;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_UVMETERANIMATION_H
