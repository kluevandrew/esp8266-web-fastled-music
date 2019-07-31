//
// Created by Андрей Клюев on 2019-07-30.
//

#include <Application.h>
#include "AudioAction.h"

void AudioAction::operator()(AsyncWebServerRequest *request) {
    auto audioAnalyzer = Application::getInstance().getAudioAnalyzer();
    audioAnalyzer->analyze();

    DynamicJsonDocument response(1024);

    response["lastMajorPeak"] = audioAnalyzer->getLastMajorPeak();
    response["low"] = audioAnalyzer->getLow();
    response["mid"] = audioAnalyzer->getMid();
    response["high"] = audioAnalyzer->getHigh();

    json(request, response);
}

