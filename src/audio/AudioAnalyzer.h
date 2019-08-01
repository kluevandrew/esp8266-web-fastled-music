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
#ifndef ESP8266_WEB_FASTLED_MUSIC_AUDIOANALYZER_H
#define ESP8266_WEB_FASTLED_MUSIC_AUDIOANALYZER_H


#include "arduinoFFT.h"
#include "config/config.h"

class AudioAnalyzer;

class AudioAnalyzer {
public:
    /**
       Constructor
    */
    explicit AudioAnalyzer();

    /**
       Destructor
    */
    ~AudioAnalyzer();

    void analyze();

    double getLastMajorPeak();

    double getLow();

    double getMid();

    double getHigh();

    const double *getVReal() const;

    double getMaxFrequency() const;

private:
    arduinoFFT fft;
    static const uint16_t samples = ADC_SAMPLES; // This value MUST ALWAYS be a power of 2
    const double samplingFrequency = 20000;
    unsigned int samplingPeriodUS;
    unsigned long microseconds{};
    double vReal[samples]{};
    double vImag[samples]{};
    double lastMajorPeak{};
    double maxFrequency{};

private:
    uint8_t high{};
    uint8_t low{};
    uint8_t mid{};

    /**
     * Analyze data on analog channel
     */
    void sampling();
};


#endif //ESP8266_WEB_FASTLED_MUSIC_AUDIOANALYZER_H
