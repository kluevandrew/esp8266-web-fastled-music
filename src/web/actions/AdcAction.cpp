//
// Created by Андрей Клюев on 2019-07-31.
//

#include <Application.h>
#include "AdcAction.h"

void AdcAction::operator()(AsyncWebServerRequest *request) {
    auto adc = Application::getInstance().getAdc();

    DynamicJsonDocument response(1024);

    response["ch0"] = adc->analogRead(0);
    response["ch1"] = adc->analogRead(1);
    response["ch2"] = adc->analogRead(2);
    response["ch3"] = adc->analogRead(3);
    response["ch4"] = adc->analogRead(4);
    response["ch5"] = adc->analogRead(5);
    response["ch7"] = adc->analogRead(7);

    json(request, response);
}
