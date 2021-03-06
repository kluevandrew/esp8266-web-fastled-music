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
#ifndef ESP8266_WEB_FASTLED_MUSIC_CONFIGURABLELEDANIMATION_HPP
#define ESP8266_WEB_FASTLED_MUSIC_CONFIGURABLELEDANIMATION_HPP


#include <Application.h>

class ConfigurableLedAnimation : public LedAnimation {
protected:
    template<typename T>
    T getOption(const String &key, T defaultValue) {
        String namedKey = getName() + "." + key;
        return Application::getInstance().getSettingsStorage().get<T>(namedKey, defaultValue);
    }

    FORCE_INLINE int getHueOption(const String &key, int defaultValue) {
        return min(360, max(0, getOption<int>(key, defaultValue)));
    }

    FORCE_INLINE uint8_t getLimitedByteOption(const String &key, int defaultValue, uint8_t min = 0, uint8_t max = 255) {
        uint8_t value = getOption(key, defaultValue);
        if (value < min) {
            return min;
        }
        if (value > max) {
            return max;
        }
        return value;
    }
};


#endif //ESP8266_WEB_FASTLED_MUSIC_CONFIGURABLELEDANIMATION_HPP
