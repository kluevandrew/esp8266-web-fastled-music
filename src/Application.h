//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_APPLICATION_H
#define ESP8266_WEB_FASTLED_MUSIC_APPLICATION_H

#include "config/config.h"
#include <FastLED.h>
#include <adc/ExternalADC.h>
#include <audio/AudioAnalyzer.h>
#include <web/WebServer.h>
#include <led/Led.h>

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

    void setup();
    void loop();
private:
    ExternalADC *adc;
    AudioAnalyzer *audioAnalyzer;
    WebServer *webServer;
    Led *led;

    Application();
    ~Application() = default; // и деструктор

    static void setupWifi();
    static void setupWifiClient();
    static void setupWifiAP();
};


#endif //ESP8266_WEB_FASTLED_MUSIC_APPLICATION_H
