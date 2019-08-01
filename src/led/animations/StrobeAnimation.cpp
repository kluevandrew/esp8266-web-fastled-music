//
// Created by Андрей Клюев on 2019-07-31.
//

#include "StrobeAnimation.h"

StrobeAnimation::StrobeAnimation(const JsonObject& options) {
    if (options.containsKey("delay")) {
        delay = options["delay"];
    }

    if (options.containsKey("colorOn")) {
        JsonArray colorOnValues = options["colorOn"];
        colorOn = CRGB(colorOnValues[0], colorOnValues[1], colorOnValues[2]);
    }

    if (options.containsKey("colorOff")) {
        JsonArray colorOffValues = options["colorOff"];
        colorOff = CRGB(colorOffValues[0], colorOffValues[1], colorOffValues[2]);
    }
}

void StrobeAnimation::animate() {
    EVERY_N_MILLIS_I(timingObj, delay) {
        timingObj.setPeriod(delay); // @fixme must be exactly each set on creation
        FastLED.showColor(state ? colorOn : colorOff);
        state = !state;
    }
}


