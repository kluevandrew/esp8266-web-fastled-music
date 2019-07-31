//
// Created by Андрей Клюев on 2019-07-30.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_INDEXACTION_H
#define ESP8266_WEB_FASTLED_MUSIC_INDEXACTION_H

#include "WebAction.h"

class IndexAction: public WebAction {
public:
    void operator()(AsyncWebServerRequest *request) override;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_INDEXACTION_H
