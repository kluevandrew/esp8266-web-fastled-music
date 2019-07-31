//
// Created by Андрей Клюев on 2019-07-31.
//

#include <Application.h>
#include <led/AnimationFactory.h>
#include "SetAnimationAction.h"

void
SetAnimationAction::operator()(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    DynamicJsonDocument requestBody(1024);
    deserializeJson(requestBody, (const char *) data);

    if (!requestBody.containsKey("name")) {
        jsonBadRequest(request);
        return;
    }
    String name = requestBody["name"];

    LedAnimation* animation;
    if (requestBody.containsKey("options")) {
        JsonObject options = requestBody["options"];
        animation = AnimationFactory::create(name, options);
    } else {
        animation = AnimationFactory::create(name);
    }

    Application::getInstance().getLed()->setAnimation(animation);

    requestBody["status"] = "ok";
    json(request, requestBody);
}
