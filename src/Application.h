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
#ifndef ESP8266_WEB_FASTLED_MUSIC_APPLICATION_H
#define ESP8266_WEB_FASTLED_MUSIC_APPLICATION_H

#include "config/config.h"
#define FASTLED_INTERNAL
#include <FastLED.h>
#include <adc/ExternalADC.h>
#include <audio/AudioAnalyzer.h>
#include <web/WebServer.h>
#include <led/Led.h>
#include <wifi/WiFiManager.h>
#include <storage/SettingsStorage.h>

class Application {
public:
    static Application &getInstance() {
        static Application s;
        return s;
    }

    Application(Application const &) = delete;

    Application &operator=(Application const &) = delete;

    ExternalADC *getAdc();

    AudioAnalyzer *getAudioAnalyzer();

    WebServer *getWebServer();

    Led *getLed();

    SettingsStorage &getSettingsStorage();

    void setup();

    void loop();

private:
    ExternalADC *adc;
    AudioAnalyzer *audioAnalyzer;
    WebServer *webServer;
    Led *led;
    SettingsStorage *settingsStorage;

    Application();

    ~Application() = default; // и деструктор

    bool apMode = false;
};


#endif //ESP8266_WEB_FASTLED_MUSIC_APPLICATION_H
