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
#include "BlendwaveAnimation.h"

BlendwaveAnimation::BlendwaveAnimation(const JsonObject &options) {
    if (options.containsKey("bpm1")) { bpm1 = options["bpm1"]; }
    if (options.containsKey("bpm2")) { bpm2 = options["bpm2"]; }
}

void BlendwaveAnimation::animate(CRGB *strip) {
    uint8_t speed = beatsin8(bpm1, 0, 255);

    color1 = blend(
            CHSV(beatsin8(3, 0, 255), 255, 255),
            CHSV(beatsin8(4, 0, 255), 255, 255),
            speed
    );
    color2 = blend(
            CHSV(beatsin8(4, 0, 255), 255, 255),
            CHSV(beatsin8(3, 0, 255), 255, 255),
            speed
    );

    uint8_t loc = beatsin8(bpm2, 0, LED_LENGTH - 1);
    fill_gradient_RGB(strip, 0, color1, loc, color1);
    fill_gradient_RGB(strip, loc, color2, LED_LENGTH - 1, color1);
    FastLED.show();
}
