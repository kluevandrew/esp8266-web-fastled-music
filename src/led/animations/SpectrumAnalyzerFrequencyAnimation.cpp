//
// Created by Андрей Клюев on 2019-08-01.
//

#include "SpectrumAnalyzerFrequencyAnimation.h"
#include <Application.h>

SpectrumAnalyzerFrequencyAnimation::SpectrumAnalyzerFrequencyAnimation(const JsonObject &options) : FrequencyAnimation(
        options) {
    if (options.containsKey("startColor")) {
        startColor = options["startColor"];
    }

    if (options.containsKey("step")) {
        step = options["step"];
    }

    if (options.containsKey("smooth")) {
        step = options["smooth"];
    }
}

void SpectrumAnalyzerFrequencyAnimation::animate() {
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

    byte huEindex = startColor;
    for (int i = 0; i < LED_LENGTH / 2; i++) {
        byte brightness = map(
                (long) frequencies[(int) floor(((double) LED_LENGTH / 2 - i) / freq_to_stripe)],
                0,
                (long) maxFrequency,
                0,
                255
        );
        brightness = constrain(brightness, 0, 255);

        led->setColorAt(i, CHSV(huEindex, 255, brightness));
        led->setColorAt(LED_LENGTH - i - 1, led->getColorAt(i));
        huEindex += step;
        if (huEindex > 255) {
            huEindex = 0;
        }
    }

    FastLED.show();
}
