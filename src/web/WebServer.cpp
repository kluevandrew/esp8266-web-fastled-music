/*
 * This file is part of the esp8266-web-fastled-music distribution (https://github.com/kluevandrew/esp8266-web-fastled-music).
 * Copyright (c) 2019, Kluev Andrew <kluev.andrew@gmail.com>.
 *
 * esp8266-web-fastled-music is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
 *
 * You are free to:
 *   Share — copy and redistribute the material in any medium or format
 *   Adapt — remix, transform, and build upon the material
 *
 * Under the following terms:
 *   Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
 *   NonCommercial — You may not use the material for commercial purposes.
 *   ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.
 *   No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.
 *
 * For additional information, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
 */
#include "WebServer.h"
#include <web/actions/IndexAction.h>
#include <web/actions/AudioAction.h>
#include <web/actions/AdcAction.h>
#include <web/actions/SetAnimationAction.h>
#include <web/actions/PutSettingsAction.h>
#include <web/actions/GetSettingsAction.h>
#include <web/actions/DeleteSettingsAction.h>
#include <web/actions/WiFiSetAction.h>
#include <web/actions/WiFiResetAction.h>
#include <web/actions/WiFiScanAction.h>

WebServer::WebServer() {
    configure();
}

WebServer::~WebServer() = default;

void WebServer::listen() {
    server.begin();
}

void WebServer::configure() {
    server.on("/api/v1/", HTTP_GET, IndexAction());
    server.on("/api/v1/audio/", HTTP_GET, AudioAction());
    server.on("/api/v1/adc/", HTTP_GET, AdcAction());

    server.on("/api/v1/animation/", HTTP_POST, emptyAction(), nullptr, SetAnimationAction());
    server.on("/api/v1/wifi/", HTTP_POST, emptyAction(), nullptr, WiFiSetAction());
    server.on("/api/v1/wifi/", HTTP_DELETE, WiFiResetAction());
    server.on("/api/v1/wifi/", HTTP_GET, WiFiScanAction());
    server.on("/api/v1/settings/", HTTP_GET, GetSettingsAction());
    server.on("/api/v1/settings/", HTTP_PUT, emptyAction(), nullptr, PutSettingsAction());
    server.on("/api/v1/settings/", HTTP_DELETE, DeleteSettingsAction());

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");;
    server.onNotFound(&WebServer::notFound);
}

void WebServer::notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
