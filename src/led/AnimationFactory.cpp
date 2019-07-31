//
// Created by Андрей Клюев on 2019-07-31.
//

#include "AnimationFactory.h"
#include "ArduinoJson.h"
#include <led/animations/NoopAnimation.h>
#include <led/animations/StrobeAnimation.h>
#include <led/animations/SimpleFrequencyAnimation.h>
#include <led/animations/FrequencyStrobeAnimation.h>
#include <led/animations/RunningFrequencyAnimation.h>
#include <led/animations/SpectrumAnalyzerFrequencyAnimation.h>

LedAnimation* AnimationFactory::create(const String& name) {
    create(name, JsonObject());
}

LedAnimation *AnimationFactory::create(const String &name, const JsonObject& options) {
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

    return new NoopAnimation();
}
