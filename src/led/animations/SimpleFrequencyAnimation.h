//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_SIMPLEFREQUENCYANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_SIMPLEFREQUENCYANIMATION_H


#include "FrequencyAnimation.h"

class SimpleFrequencyAnimation: public FrequencyAnimation {
public:
    SimpleFrequencyAnimation() = default;
    explicit SimpleFrequencyAnimation(const JsonObject& options);
    ~SimpleFrequencyAnimation() override = default;

    void animate() override;

protected:
    String direction = "ltr";
};


#endif //ESP8266_WEB_FASTLED_MUSIC_SIMPLEFREQUENCYANIMATION_H
