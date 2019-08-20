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
#include "SpectrumAnalyzerFrequencyAnimation.h"
#include <Application.h>

void SpectrumAnalyzerFrequencyAnimation::animate() {
    uint8_t startColor = getLimitedByteOption("startColor", 0, 255);
    uint8_t step = getLimitedByteOption("step", 5, 1);
    uint8_t smooth = getLimitedByteOption("smooth", 2, 1);

    auto led = Application::getInstance().getLed();
    calculateBright();
    auto audioAnalyzer = Application::getInstance().getAudioAnalyzer();

    auto vReal = audioAnalyzer->getVReal();

    for (int i = 0; i < (ADC_SAMPLES / 2); i++) {
        if (frequencies[i] < vReal[i]) {
            frequencies[i] = vReal[i];
        }
        if (frequencies[i] > 0) {
            frequencies[i] -= smooth;
        } else {
            frequencies[i] = 0;
        }
    }

    int freq_to_stripe = LED_LENGTH / 2 / 40; // /2 cause symmetry, and /20 cause 20 frequencies

    byte hueIndex = startColor;
    for (int i = 0; i < LED_LENGTH / 2; i++) {
        byte brightness = map(
                (long) frequencies[(int) floor(((double) LED_LENGTH / 2 - i) / freq_to_stripe)],
                0,
                (long) maxFrequency,
                0,
                255
        );
        brightness = mapBright(constrain(brightness, 0, 255));

        led->setColorAt(i, CHSV(hueIndex, 255, brightness));
        led->setColorAt(LED_LENGTH - i - 1, led->getColorAt(i));
        hueIndex += step;
        if (hueIndex > 255) {
            hueIndex = 0;
        }
    }

    FastLED.show();
}
