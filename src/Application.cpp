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
#include "Application.h"
#include <led/Led.h>
#include <ArduinoOTA.h>

Application::Application() {
    Serial.begin(115200);
    Serial.println();
    SPIFFS.begin();
    settingsStorage = new SettingsStorage();
    adc = new ExternalADC();
    audioAnalyzer = new AudioAnalyzer();
    webServer = new WebServer();
    led = new Led();
}

ExternalADC *Application::getAdc() {
    return adc;
}

AudioAnalyzer *Application::getAudioAnalyzer() {
    return audioAnalyzer;
}

WebServer *Application::getWebServer() {
    return webServer;
}

Led *Application::getLed() {
    return led;
}

SettingsStorage &Application::getSettingsStorage() {
    return *settingsStorage;
}

void Application::setup() {
    apMode = WiFiManager::autoConnect();

#ifdef OTA_PASSWORD
    ArduinoOTA.setPassword(OTA_PASSWORD);
#endif
    ArduinoOTA.onStart([this]() {
        Serial.println("OTA: Start updating");
        this->webServer->sendEvent("ota_start");
    });
    ArduinoOTA.onEnd([this]() {
        Serial.println("OTA: Done updating");
        if (ArduinoOTA.getCommand() == U_SPIFFS) {
            Application::getInstance().getSettingsStorage().save();
        }
        ESP.restart();
    });
    ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
        DynamicJsonDocument message(256);
        message["progress"] = progress;
        message["total"] = total;

        this->webServer->sendEvent("ota_progress", message);
    });
    ArduinoOTA.onError([this](ota_error_t error) {
        Serial.printf("OTA: Error[%u]: ", error);
        String errorMessage;
        if (error == OTA_AUTH_ERROR) {
            errorMessage = "Auth Failed";
        } else if (error == OTA_BEGIN_ERROR) {
            errorMessage = "Begin Failed";
        } else if (error == OTA_CONNECT_ERROR) {
            errorMessage = "Connect Failed";
        } else if (error == OTA_RECEIVE_ERROR) {
            errorMessage = "Receive Failed";
        } else if (error == OTA_END_ERROR) {
            errorMessage = "End Failed";
        }
        Serial.println(errorMessage);
        DynamicJsonDocument message(256);
        message["error"] = error;
        message["message"] = errorMessage;

        this->webServer->sendEvent("ota_error", message);
        ESP.restart();
    });
    ArduinoOTA.begin();

    webServer->listen();
}

void Application::loop() {
    if (!apMode) {
        ArduinoOTA.handle();
    }
#ifndef DISABLE_LED
    led->animate();
#endif
}
