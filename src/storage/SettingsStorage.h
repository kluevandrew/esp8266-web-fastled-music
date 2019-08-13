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
#ifndef ESP8266_WEB_FASTLED_MUSIC_SETTINGSSTORAGE_H
#define ESP8266_WEB_FASTLED_MUSIC_SETTINGSSTORAGE_H


#include <string>
#include "ArduinoJson.h"
#include "config/config.h"

class SettingsStorage {
public:
    explicit SettingsStorage();

    ~SettingsStorage() = default;

    void load();

    void save();

    template<typename T>
    bool set(const String &key, T value) const {
        return jsonDocument->getOrAddMember(key).set(value);
    }

    bool set(const String &key, JsonVariant value) {
        return jsonDocument->getOrAddMember(key).set(value);
    }

    template<typename T>
    FORCE_INLINE T get(const String &key, T defaultValue) const {
        if (!has(key)) {
            return defaultValue;
        }
        return (*jsonDocument)[key];
    }

    FORCE_INLINE JsonVariant get(const String &key, JsonVariant defaultValue) {
        return jsonDocument->getMember(key);
    }

    FORCE_INLINE JsonVariant get(const String &key) {
        return jsonDocument->getMember(key);
    }

    FORCE_INLINE bool has(const String &key) const {
        return jsonDocument->containsKey(key);
    }

    void remove(const String &key) {
        jsonDocument->remove(key);
    }

    void truncate();

private:
    DynamicJsonDocument *jsonDocument = new DynamicJsonDocument(SETTINGS_CAPACITY);

};


#endif //ESP8266_WEB_FASTLED_MUSIC_SETTINGSSTORAGE_H
