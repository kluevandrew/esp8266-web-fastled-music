//
// Created by Андрей Клюев on 2019-07-30.
//

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
