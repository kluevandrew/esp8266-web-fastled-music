//
// Created by Андрей Клюев on 2019-08-01.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_FREQUENCYSTROBEANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_FREQUENCYSTROBEANIMATION_H

#include "FrequencyAnimation.h"

class FrequencyStrobeAnimation : public FrequencyAnimation {
public:
    FrequencyStrobeAnimation() = default;

    explicit FrequencyStrobeAnimation(const JsonObject &options);

    ~FrequencyStrobeAnimation() override = default;

    void animate() override;

private:
    uint8_t mode = 0;
    uint8_t emptyColor = HUE_PURPLE;

    void drawHighs();

    void drawMids();

    void drawLows();

    void drawSilence();
};


#endif //ESP8266_WEB_FASTLED_MUSIC_FREQUENCYSTROBEANIMATION_H
