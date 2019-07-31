//
// Created by Андрей Клюев on 2019-07-30.
//

#include "IndexAction.h"

void IndexAction::operator()(AsyncWebServerRequest *request) {
    DynamicJsonDocument response(1024);

    response["version"] = "0.0.1";

    JsonObject developer = response.createNestedObject("developer");
    developer["name"] = "Andrew Kluev";
    developer["email"] = "kluev.andrew@gmail.com";

    json(request, response);
}
