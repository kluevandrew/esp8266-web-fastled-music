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

DotBeatAnimation::DotBeatAnimation(const JsonObject &options) {
    if (options.containsKey("middleHue")) { middleHue = options["middleHue"]; }
    if (options.containsKey("innerHue")) { innerHue = options["innerHue"]; }
    if (options.containsKey("outerHue")) { outerHue = options["outerHue"]; }
    if (options.containsKey("middleSaturation")) { middleSaturation = options["middleSaturation"]; }
    if (options.containsKey("innerSaturation")) { innerSaturation = options["innerSaturation"]; }
    if (options.containsKey("outerSaturation")) { outerSaturation = options["outerSaturation"]; }
    if (options.containsKey("bright")) { bright = options["bright"]; }
    if (options.containsKey("bpm")) { bpm = options["bpm"]; }
    if (options.containsKey("fade")) { fade = options["fade"]; }
}

void DotBeatAnimation::animate(CRGB *strip) {
    uint8_t inner = beatsin8(bpm, LED_LENGTH / 4, LED_LENGTH / 4 * 3);    // Move 1/4 to 3/4
    uint8_t outer = beatsin8(bpm, 0, LED_LENGTH - 1);               // Move entire length
    uint8_t middle = beatsin8(bpm, LED_LENGTH / 3, LED_LENGTH / 3 * 2);   // Move 1/3 to 2/3

    strip[middle] = CHSV(middleHue, middleSaturation, bright);
    strip[inner] = CHSV(innerHue, innerSaturation, bright);
    strip[outer] = CHSV(outerHue, outerSaturation, bright);

    nscale8(strip, LED_LENGTH, fade);
    FastLED.show();
}

