//
// Created by Андрей Клюев on 2019-07-30.
//

#include "WebAction.h"

void WebAction::json(AsyncWebServerRequest *request, const DynamicJsonDocument &response) {
    json(request, response, 200);
}

void WebAction::json(AsyncWebServerRequest *request, const DynamicJsonDocument& response, int code) {
    String json;
    serializeJson(response, json);
    request->send(code, "application/json", json);
}

void WebAction::operator()(AsyncWebServerRequest *request) {}

void WebAction::operator()(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {}

void WebAction::jsonBadRequest(AsyncWebServerRequest *request) {
    DynamicJsonDocument response(1024);

    response["error"] = "Bad request";

    json(request, response, 400);
}

