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
#include "IndexAction.h"
#include <ArduinoOTA.h>
#include <config/config.h>
#include <Application.h>

void IndexAction::operator()(AsyncWebServerRequest *request) {
    DynamicJsonDocument response(SETTINGS_CAPACITY + 512);

    response["version"] = "0.2.0";

    JsonObject developer = response.createNestedObject("developer");
    developer["name"] = "Andrew Kluev";
    developer["email"] = "kluev.andrew@gmail.com";

    JsonObject info = response.createNestedObject("info");
    info["ota_hostname"] = ArduinoOTA.getHostname();
#if defined(OTA_PASSWORD)
    info["ota_secured"] = true;
#else
    info["ota_secured"] = false;
#endif
    info["vcc"] = ESP.getVcc();
    info["freeHeap"] = ESP.getFreeHeap();
    info["maxFreeBlockSize"] = ESP.getMaxFreeBlockSize();
    info["freeContStack"] = ESP.getFreeContStack();
    info["chipId"] = ESP.getChipId();
    info["coreVersion"] = ESP.getCoreVersion();
    info["sdkVersion"] = ESP.getSdkVersion();
    info["bootVersion"] = ESP.getBootVersion();
    info["bootMode"] = ESP.getBootMode();
    info["cpuFreqMHz"] = ESP.getCpuFreqMHz();
    info["flashChipId"] = ESP.getFlashChipId();
    info["flashChipVendorId"] = ESP.getFlashChipVendorId();
    info["flashChipRealSize"] = ESP.getFlashChipRealSize();
    info["flashChipSize"] = ESP.getFlashChipSize();
    info["flashChipSpeed"] = ESP.getFlashChipSpeed();
    info["resetReason"] = ESP.getResetReason();
    info["resetInfo"] = ESP.getResetInfo();
    info["sketchSize"] = ESP.getSketchSize();
    info["freeSketchSpace"] = ESP.getFreeSketchSpace();
    info["sketchMD5"] = ESP.getSketchMD5();

    auto settings = Application::getInstance().getSettingsStorage();
    auto options = response.createNestedObject("options");
    options.set(settings.getJsonDocument()->as<JsonObject>());

    json(request, response);
}
