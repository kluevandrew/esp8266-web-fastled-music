//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_FREQUENCYANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_FREQUENCYANIMATION_H

#include "LedAnimation.h"
#include <FastLED.h>

class FrequencyAnimation: public LedAnimation {
public:
    FrequencyAnimation() = default;
    explicit FrequencyAnimation(const JsonObject& options);
    ~FrequencyAnimation() override = default;

protected:
    int smoothStep = 20;
    byte minimalBright = 30;
    double smoothFrequency = 0.8;
    double maxFrequencyCoefficient = 1.2;
    double averageCoefficient = 0.006;
    uint8_t lowColor = HUE_RED;
    uint8_t midColor = HUE_GREEN;
    uint8_t highColor = HUE_BLUE;

    int bright[3] = {0, 0, 0};
    boolean flashes[3] = {false, false, false};
    boolean running[3] = {false, false, false};
    double maxFrequency = 0.0;
    double averageLevels[3] = {0.0, 0.0, 0.0};
    double levels[3] = {0.0, 0.0, 0.0};

    void calculateBright();
};


#endif //ESP8266_WEB_FASTLED_MUSIC_FREQUENCYANIMATION_H
