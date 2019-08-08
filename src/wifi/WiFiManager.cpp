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
#include <ESP8266WiFi.h>
#include <config/config.h>
#include "WiFiManager.h"

WiFiManager::WiFiManager() {
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
}

WiFiManager::~WiFiManager() = default;

void WiFiManager::autoConnect() {
    connectSTA();
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Client Failed! Fallback to AP mode.\n");
        connectAP();
        Serial.print("IP Address: ");
        Serial.println(WiFi.softAPIP());
    } else {
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
    WiFi.scanNetworks(true, true);
}

void WiFiManager::reset() {
    WiFi.disconnect(true);
    WiFi.softAPdisconnect(true);
    ESP.reset();
}

void WiFiManager::connect(const String &ssid, const String &pass) {
    WiFi.begin(ssid.c_str(), pass.c_str(), 0, nullptr, false);
    ESP.reset();
}

void WiFiManager::connect(const String &ssid) {
    WiFi.begin(ssid.c_str(), nullptr, 0, nullptr, false);
    ESP.reset();
}

void WiFiManager::connectSTA() {
    WiFi.mode(WIFI_STA);
    WiFi.begin();
}

void WiFiManager::connectAP() {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
#if defined(WIFI_AP_PASS)
    WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASS);
#else
    WiFi.softAP(WIFI_AP_SSID);
#endif
}

WiFiManager::ScanResult WiFiManager::scan() {
    WiFiManager::ScanResult result;

    int count = WiFi.scanComplete();
    if (count == WIFI_SCAN_FAILED) {
        WiFi.scanNetworks(true, true);
    }

    if (count < 0) {
        result.running = true;
        result.count = 0;
        return result;
    }

    result.running = false;
    result.count = count;
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            WiFiManager::Network network;
            network.ssid = WiFi.SSID(i);
            network.rssi = WiFi.RSSI(i);
            network.bssid = WiFi.BSSIDstr(i);
            network.encryption = WiFi.encryptionType(i) == ENC_TYPE_NONE;
            network.channel = WiFi.channel(i);
            network.isHidden = WiFi.isHidden(i);
            result.networks.push_back(network);
        }
        WiFi.scanDelete();
        if (WiFi.scanComplete() == WIFI_SCAN_FAILED) {
            WiFi.scanNetworks(true, true);
        }
    }

    return result;
}
