//
// Created by Андрей Клюев on 2019-08-01.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_RUNNINGFREQUENCYANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_RUNNINGFREQUENCYANIMATION_H

#include "FrequencyAnimation.h"

class RunningFrequencyAnimation : public FrequencyAnimation {
public:
    RunningFrequencyAnimation() = default;

    explicit RunningFrequencyAnimation(const JsonObject &options);

    ~RunningFrequencyAnimation() override = default;

    void animate() override;

private:
    uint8_t mode = 0;
    uint8_t emptyColor = HUE_PURPLE;
    uint8_t speed = 11;

    unsigned long stepTimer = 0;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_RUNNINGFREQUENCYANIMATION_H
