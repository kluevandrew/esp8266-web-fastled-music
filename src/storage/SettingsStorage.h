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

class SettingsStorage {
public:
    explicit SettingsStorage();

    ~SettingsStorage() = default;

    void load();

    void save();

    DynamicJsonDocument *jsonDocument = new DynamicJsonDocument(4096);

    // set(const char *key, bool value)
    FORCE_INLINE bool set(const char *key, bool value) const {
        return jsonDocument->getOrAddMember(key).set(value);
    }

    // set(const char *key, double value);
    // set(const char *key, float value);
    template<typename T>
    FORCE_INLINE bool
    set(const char *key, T value, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0) const {
        return jsonDocument->getOrAddMember(key).set(value);
    }

    // set(const char *key, char)
    // set(const char *key, signed short)
    // set(const char *key, signed int)
    // set(const char *key, signed long)
    // set(const char *key, signed char)
    template<typename T>
    FORCE_INLINE bool set(
            const char *key,
            T value,
            typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value>::type * =
            0) const {
        return jsonDocument->getOrAddMember(key).set(value);
    }

    // set(const char *key, unsigned short)
    // set(const char *key, unsigned int)
    // set(const char *key, unsigned long)
    template<typename T>
    FORCE_INLINE bool set(
            const char *key,
            T value,
            typename std::enable_if<std::is_integral<T>::value &&
                                    std::is_unsigned<T>::value>::type * = 0) const {
        return jsonDocument->getOrAddMember(key).set(value);
    }


    // set(const char *key, const std::string&)
    // set(const char *key, const String&)
    template<typename T>
    FORCE_INLINE bool set(
            const char *key,
            const T &value,
            typename std::enable_if<ARDUINOJSON_NAMESPACE::IsString<T>::value>::type * = 0) const {
        return jsonDocument->getOrAddMember(key).set(value);
    }

    // set(const char *key, char*)
    // set(const char *key, const __FlashStringHelper*)
    template<typename T>
    FORCE_INLINE bool set(
            const char *key,
            T *value,
            typename std::enable_if<ARDUINOJSON_NAMESPACE::IsString<T *>::value>::type * = 0) const {
        return jsonDocument->getOrAddMember(key).set(value);
    }

    // set(const char *key, const char*);
    FORCE_INLINE bool set(const char *key, const char *value) const {
        return jsonDocument->getOrAddMember(key).set(value);
    }

    // set(const char *key, VariantRef)
    // set(const char *key, VariantConstRef)
    // set(const char *key, ArrayRef)
    // set(const char *key, ArrayConstRef)
    // set(const char *key, ObjectRef)
    // set(const char *key, ObjecConstRef)
    // set(const char *key, const JsonDocument&)
    template<typename TVariant>
    typename std::enable_if<ARDUINOJSON_NAMESPACE::IsVisitable<TVariant>::value, bool>::type
    set(const char *key, const TVariant &value) const {
        return jsonDocument->getOrAddMember(key).set(value);
    };

    // get(bool value)
    FORCE_INLINE bool get(const char *key) const {
        return jsonDocument->getMember(key);
    }

    // get(const char *key);
    // get(const char *key);
    template<typename T>
    FORCE_INLINE T
    get(const char *key, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0) const {
        return jsonDocument->getMember(key);
    }

    // get(char)
    // get(signed short)
    // get(signed int)
    // get(signed long)
    // get(signed char)
    template<typename T>
    FORCE_INLINE T get(
            const char *key,
            typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value>::type * =
            0) const {
        return jsonDocument->getMember(key);
    }

    // get(unsigned short)
    // get(unsigned int)
    // get(unsigned long)
    template<typename T>
    FORCE_INLINE T get(
            const char *key,
            typename std::enable_if<std::is_integral<T>::value &&
                                    std::is_unsigned<T>::value>::type * = 0) const {
        return jsonDocument->getMember(key);
    }


    // get(const std::string&)
    // get(const String&)
    template<typename T>
    FORCE_INLINE T get(
            const char *key,
            typename std::enable_if<ARDUINOJSON_NAMESPACE::IsString<T>::value>::type * = 0) const {
        return jsonDocument->getMember(key);
    }

    // get(char*)
    // get(const __FlashStringHelper*)
    template<typename T>
    FORCE_INLINE T get(
            const char *key,
            typename std::enable_if<ARDUINOJSON_NAMESPACE::IsString<T *>::value>::type * = 0) const {
        return (const char *) jsonDocument->getMember(key);
    }

    // get(VariantRef)
    // get(VariantConstRef)
    // get(ArrayRef)
    // get(ArrayConstRef)
    // get(ObjectRef)
    // get(ObjecConstRef)
    // get(const JsonDocument&)
    template<typename TVariant>
    typename std::enable_if<ARDUINOJSON_NAMESPACE::IsVisitable<TVariant>::value, bool>::type
    get(const char *key) const {
        return jsonDocument->getMember(key);
    };

    // has(const char *key)
    FORCE_INLINE bool has(const char *key) const {
        return jsonDocument->containsKey(key);
    }
};


#endif //ESP8266_WEB_FASTLED_MUSIC_SETTINGSSTORAGE_H
