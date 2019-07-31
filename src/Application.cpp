#include <led/Led.h>
#include "Application.h"

Application::Application() {
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

void Application::setup() {
    Serial.begin(115200);

    Serial.println();

    setupWifi();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    SPIFFS.begin();

    webServer->listen();
}

void Application::loop() {
    led->animate();
}

void Application::setupWifi() {
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    setupWifiClient();
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Client Failed! Fallback to AP mode.\n");
        setupWifiAP();
        return;
    }
}

void Application::setupWifiClient() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_CLIENT_SSID, WIFI_CLIENT_PASS);

}

void Application::setupWifiAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASS);
}
