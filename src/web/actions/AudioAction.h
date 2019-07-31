//
// Created by Андрей Клюев on 2019-07-30.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_AUDIOACTION_H
#define ESP8266_WEB_FASTLED_MUSIC_AUDIOACTION_H


#include <audio/AudioAnalyzer.h>
#include "WebAction.h"

class AudioAction: public WebAction {
public:
    void operator()(AsyncWebServerRequest *request) override;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_AUDIOACTION_H
