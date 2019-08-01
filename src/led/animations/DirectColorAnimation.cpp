//
// Created by Андрей Клюев on 2019-08-01.
//

#include "DirectColorAnimation.h"

DirectColorAnimation::DirectColorAnimation(const JsonObject &options) {
    if (options.containsKey("color")) {
        color = options["color"];
    }

    if (options.containsKey("saturation")) {
        saturation = options["saturation"];
    }

    if (options.containsKey("bright")) {
        bright = options["bright"];
    }
}

void DirectColorAnimation::animate() {
    if (!done) {
       FastLED.showColor(CHSV(color, saturation, bright));
    }
}
