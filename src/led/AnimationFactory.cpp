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
#include "AnimationFactory.h"
#include "ArduinoJson.h"
#include <led/animations/NoopAnimation.h>
#include <led/animations/StrobeAnimation.h>
#include <led/animations/SimpleFrequencyAnimation.h>
#include <led/animations/FrequencyStrobeAnimation.h>
#include <led/animations/RunningFrequencyAnimation.h>
#include <led/animations/SpectrumAnalyzerFrequencyAnimation.h>
#include <led/animations/RainbowAnimation.h>
#include <led/animations/DirectColorAnimation.h>
#include <led/animations/DynamicColorAnimation.h>
#include <led/animations/DotBeatAnimation.h>
#include <led/animations/BlendwaveAnimation.h>
#include <led/animations/BlurAnimation.h>
#include <led/animations/ConfettiAnimation.h>

LedAnimation *AnimationFactory::create(const String &name) {
    create(name, JsonObject());
}

LedAnimation *AnimationFactory::create(const String &name, const JsonObject &options) {
    if (name == "strobe") {
        return new StrobeAnimation(options);
    }

    if (name == "frequency") {
        return new SimpleFrequencyAnimation(options);
    }

    if (name == "frequency_strobe") {
        return new FrequencyStrobeAnimation(options);
    }

    if (name == "frequency_running") {
        return new RunningFrequencyAnimation(options);
    }

    if (name == "spectrum") {
        return new SpectrumAnalyzerFrequencyAnimation(options);
    }

    if (name == "rainbow") {
        return new RainbowAnimation(options);
    }

    if (name == "direct") {
        return new DirectColorAnimation(options);
    }

    if (name == "dynamic") {
        return new DynamicColorAnimation(options);
    }

    if (name == "dot_beat") {
        return new DotBeatAnimation(options);
    }

    if (name == "blendwave") {
        return new BlendwaveAnimation(options);
    }

    if (name == "blur") {
        return new BlurAnimation(options);
    }

    if (name == "confetti") {
        return new ConfettiAnimation(options);
    }

    return new NoopAnimation();
}
