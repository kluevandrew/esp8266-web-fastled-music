//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_NOOPANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_NOOPANIMATION_H


#include "LedAnimation.h"

class NoopAnimation: public LedAnimation {
public:
    ~NoopAnimation() override = default;
    void animate() override;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_NOOPANIMATION_H
