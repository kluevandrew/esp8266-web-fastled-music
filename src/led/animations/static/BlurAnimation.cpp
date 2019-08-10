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
#include "BlurAnimation.h"

void BlurAnimation::animate(CRGB *strip) {
    uint8_t bpm = getOption("BlurAnimation.bpm", 3);

    uint8_t blurAmount = dim8_raw(beatsin8(bpm, 64, 192));       // A sinewave at 3 Hz with values ranging from 64 to 192.
    blur1d(strip, LED_LENGTH, blurAmount);                        // Apply some blurring to whatever's already on the strip, which will eventually go black.

    uint8_t i = beatsin8(9, 0, LED_LENGTH);
    uint8_t j = beatsin8(7, 0, LED_LENGTH);
    uint8_t k = beatsin8(5, 0, LED_LENGTH);

    // The color of each point shifts over time, each at a different speed.
    uint16_t ms = millis();
    strip[(i + j) / 2] = CHSV(ms / 29, 200, 255);
    strip[(j + k) / 2] = CHSV(ms / 41, 200, 255);
    strip[(k + i) / 2] = CHSV(ms / 73, 200, 255);
    strip[(k + i + j) / 3] = CHSV(ms / 53, 200, 255);

    FastLED.show();
}
