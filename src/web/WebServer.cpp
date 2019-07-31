#include <web/actions/IndexAction.h>
#include <web/actions/AudioAction.h>
#include <web/actions/AdcAction.h>
#include <web/actions/SetAnimationAction.h>
#include "WebServer.h"


WebServer::WebServer() {
    configure();
}

WebServer::~WebServer() = default;

void WebServer::listen() {
    server.begin();
}

void WebServer::configure() {
    server.on("/", HTTP_GET, IndexAction());
    server.on("/api/v1/audio", HTTP_GET, AudioAction());
    server.on("/api/v1/adc", HTTP_GET, AdcAction());

    auto setAnimation = SetAnimationAction();
    server.on("/api/v1/animation", HTTP_POST, setAnimation, nullptr, setAnimation);
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");;
    server.onNotFound(&WebServer::notFound);
}

void WebServer::notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
