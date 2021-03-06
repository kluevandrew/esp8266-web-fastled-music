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
#include "DotBeatAnimation.h"

void DotBeatAnimation::animate(CRGB *strip) {
    uint8_t middleHue = getLimitedByteOption("middle.hue", (uint8_t)HUE_PURPLE);
    uint8_t innerHue = getLimitedByteOption("inner.hue", (uint8_t)HUE_BLUE);
    uint8_t outerHue = getLimitedByteOption("outer.hue", (uint8_t)HUE_AQUA);

    uint8_t middleSaturation = getLimitedByteOption("middle.sat", 255);
    uint8_t innerSaturation = getLimitedByteOption("inner.sat", 255);
    uint8_t outerSaturation = getLimitedByteOption("outer.sat", 255);

    uint8_t middleBright = getLimitedByteOption("middle.bright", 255);
    uint8_t innerBright = getLimitedByteOption("inner.bright", 255);
    uint8_t outerBright = getLimitedByteOption("outer.bright", 255);

    uint8_t bpm = getLimitedByteOption("bpm", 33, 1);
    uint8_t fade = getLimitedByteOption("fade", 224, 1);

    uint8_t inner = beatsin8(bpm, LED_LENGTH / 4, LED_LENGTH / 4 * 3);    // Move 1/4 to 3/4
    uint8_t outer = beatsin8(bpm, 0, LED_LENGTH - 1);                     // Move entire length
    uint8_t middle = beatsin8(bpm, LED_LENGTH / 3, LED_LENGTH / 3 * 2);   // Move 1/3 to 2/3

    strip[middle] = CHSV(middleHue, middleSaturation, middleBright);
    strip[inner] = CHSV(innerHue, innerSaturation, innerBright);
    strip[outer] = CHSV(outerHue, outerSaturation, outerBright);

    nscale8(strip, LED_LENGTH, fade);
    FastLED.show();
}

