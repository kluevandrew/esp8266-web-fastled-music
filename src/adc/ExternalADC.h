//
// Created by Андрей Клюев on 2019-07-31.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_EXTERNALADC_H
#define ESP8266_WEB_FASTLED_MUSIC_EXTERNALADC_H


#include <MCP3208.h>
#include <config/config.h>

class ExternalADC {
public:
    int analogRead(int channel);

private:
    MCP3208 mcp3208 = MCP3208(ADC_CLOCK_PIN, ADC_MOSI_PIN, ADC_MISO_PIN, ADC_CS_PIN);
};


#endif //ESP8266_WEB_FASTLED_MUSIC_EXTERNALADC_H
