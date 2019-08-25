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
#include "SettingsStorage.h"
#include <FS.h>

SettingsStorage::SettingsStorage() {
    SPIFFS.begin();
    load();
}

void SettingsStorage::load() {
    File configFile = SPIFFS.open("/config.json", "r");
    if (!configFile) {
        Serial.println("Failed to open config file");
        return;
    }
    size_t size = configFile.size();
    if (size > SETTINGS_CAPACITY) {
        Serial.println("Config file size is too large");
        configFile.close();
        return;
    }

    DeserializationError error = deserializeJson(*jsonDocument, configFile);
    if (error) {
        Serial.println("Failed to read file, using default configuration");
    }

    configFile.close();
}

void SettingsStorage::save() {
    SPIFFS.remove("/config.json");

    // Open file for writing
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
        Serial.println("Failed to open config file");
        return;
    }

    serializeJson(*jsonDocument, configFile);
    configFile.close();
}

void SettingsStorage::truncate() {
    SPIFFS.remove("/config.json");
    delete jsonDocument;
    jsonDocument = new DynamicJsonDocument(SETTINGS_CAPACITY);
    save();
}

DynamicJsonDocument *SettingsStorage::getJsonDocument() const {
    return jsonDocument;
}

