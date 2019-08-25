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
#include <Application.h>
#include "AudioAnalyzer.h"

AudioAnalyzer::AudioAnalyzer() {
    fft = arduinoFFT(vReal, vImag, samples, samplingFrequency);
    samplingPeriodUS = (int) round(1000000 * (1.0 / samplingFrequency));
}

AudioAnalyzer::~AudioAnalyzer() = default;

void AudioAnalyzer::analyzeFrequency(unsigned int micLowPass, uint8_t fftLowPass) {
    sampling(micLowPass);

    fft.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
    fft.Compute(FFT_FORWARD); /* Compute FFT */
    fft.ComplexToMagnitude();
    lastMajorPeak = fft.MajorPeak();

    for (int i = 2; i < 127; i++) {
        if (vReal[i] < fftLowPass) {
            vReal[i] = 0;
        }
    }

    for (int i = 2; i < 7; i++) {
        if (vReal[i] > low) {
            low = vReal[i];
        }
    }
    for (int i = 8; i < 34; i++) {
        if (vReal[i] > mid) {
            mid = vReal[i];
        }
    }
    for (int i = 34; i < 127; i++) {
        if (vReal[i] > high) {
            high = vReal[i];
        }
    }

    maxFrequency = max(low, max(mid, high));
    DynamicJsonDocument event(256);
    event["lastMajorPeak"] = lastMajorPeak;
    Application::getInstance().getWebServer()->sendEvent("frequencyAnalyze", event);

    if (maxFrequency < 5) {
        maxFrequency = 5; // Why AlexGayver? Why?  @fixme move to params as minFrequency, make it as param of AudioAnalyzer::analyzeFrequency(uint8_t minFrequency, int lowPassFilter)
    }
}

void AudioAnalyzer::sampling(unsigned int micLowPass) {
    unsigned int lowPass = Application::getInstance().getSettingsStorage().get("global.sampling.filter", 650);
    microseconds = micros();
    for (int i = 0; i < samples; i++) {
        vReal[i] = Application::getInstance().getAdc()->analogRead(ADC_MIC_CHANNEL); // @fixme make it dynamically configurable, in case of two mics for example
        if (vReal[i] < micLowPass) {
            vReal[i] = 0;
        }
        vImag[i] = 0;
        while (micros() - microseconds < samplingPeriodUS) {
        }
        microseconds += samplingPeriodUS;
    };
}

unsigned int AudioAnalyzer::getSamplingPeriodUs() const {
    return samplingPeriodUS;
}

double AudioAnalyzer::getLastMajorPeak() {
    return lastMajorPeak;
}

double AudioAnalyzer::getLow() {
    return low;
}

double AudioAnalyzer::getMid() {
    return mid;
}

double AudioAnalyzer::getHigh() {
    return high;
}

const double *AudioAnalyzer::getVReal() const {
    return vReal;
}

double AudioAnalyzer::getMaxFrequency() const {
    return maxFrequency;
}

uint16_t AudioAnalyzer::getSamples() {
    return samples;
}

double AudioAnalyzer::getSamplingFrequency() const {
    return samplingFrequency;
}

void AudioAnalyzer::analyzeLevels() {
    bool MONO = true;
    float EXP = 1.4;
    float SMOOTH = 0.3;
    RsoundLevel = 0;
    LsoundLevel = 0;
    unsigned int lowPass = Application::getInstance().getSettingsStorage().get("global.sampling.filter", 650);

    for (byte i = 0; i < 100; i ++) {                                 // делаем 100 измерений
        RcurrentLevel = Application::getInstance().getAdc()->analogRead(ADC_MIC_CHANNEL_DIRECT); // с правого
        if (RcurrentLevel < lowPass) {
            RcurrentLevel = 0;
        }
//        if (!MONO) LcurrentLevel = Application::getInstance().getAdc()->analogRead(ADC_MIC_CHANNEL_DIRECT);                // и левого каналов

        if (RsoundLevel < RcurrentLevel) RsoundLevel = RcurrentLevel;   // ищем максимальное
//        if (!MONO) if (LsoundLevel < LcurrentLevel) LsoundLevel = LcurrentLevel;   // ищем максимальное
    }

    // фильтруем по нижнему порогу шумов
    RsoundLevel = map(RsoundLevel, 30, 4095, 0, 500);
//    if (!MONO)LsoundLevel = map(LsoundLevel, lowPass, 1023, 0, 500);

    // ограничиваем диапазон
    RsoundLevel = constrain(RsoundLevel, 0, 500);
//    if (!MONO)LsoundLevel = constrain(LsoundLevel, 0, 500);

    // возводим в степень (для большей чёткости работы)
    RsoundLevel = pow(RsoundLevel, EXP);
//    if (!MONO)LsoundLevel = pow(LsoundLevel, EXP);

    // фильтр
    RsoundLevel_f = RsoundLevel * SMOOTH + RsoundLevel_f * (1 - SMOOTH);
//    if (!MONO)LsoundLevel_f = LsoundLevel * SMOOTH + LsoundLevel_f * (1 - SMOOTH);

//    if (MONO) {
        LsoundLevel_f = RsoundLevel_f;  // если моно, то левый = правому
//    }
}
