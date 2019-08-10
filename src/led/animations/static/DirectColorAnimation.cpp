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
#include "DirectColorAnimation.h"

#define DEFAULT_HUE 0
#define DEFAULT_SATURATION 0
#define DEFAULT_BRIGHT 255
#define DEFAULT_STEP 1
#define DEFAULT_SPEED 10

void DirectColorAnimation::animate() {
    unsigned long speed = getOption("DirectColorAnimation.speed", DEFAULT_SPEED);
    int color = getOption("DirectColorAnimation.color.hue", DEFAULT_HUE);
    uint8_t bright = getOption("DirectColorAnimation.color.bright", DEFAULT_BRIGHT);
    uint8_t saturation = getOption("DirectColorAnimation.color.saturation", DEFAULT_SATURATION);
    uint8_t step = getOption("DirectColorAnimation.step", DEFAULT_STEP);

    if (color != currentColor || saturation != currentSaturation) {
        currentColor = color;
        currentSaturation = saturation;
        timer = 0;
    }

    if (millis() - timer > speed && currentBright < bright) {
        timer = millis();

        if (currentBright < bright) {
            currentBright += step;
            FastLED.showColor(CHSV(currentColor, currentSaturation, currentBright));
        }
    }
}
