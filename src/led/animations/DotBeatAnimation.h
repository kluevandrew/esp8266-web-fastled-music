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
#ifndef ESP8266_WEB_FASTLED_MUSIC_DOTBEATANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_DOTBEATANIMATION_H


#include "LedAnimation.h"
#include <FastLED.h>

class DotBeatAnimation : public LedAnimation {
public:
    DotBeatAnimation() = default;

    explicit DotBeatAnimation(const JsonObject &options);

    ~DotBeatAnimation() override = default;

    void animate() override {};

    void animate(CRGB *strip) override;

private:
    int middleHue = HUE_PURPLE;
    int innerHue = HUE_BLUE;
    int outerHue = HUE_AQUA;

    uint8_t middleSaturation = 255;
    uint8_t innerSaturation = 255;
    uint8_t outerSaturation = 255;

    uint8_t bright = 255;

    uint8_t bpm = 30;
    uint8_t fade = 224;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_DOTBEATANIMATION_H
