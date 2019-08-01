//
// Created by Андрей Клюев on 2019-07-30.
//

#include <Application.h>
#include "AudioAnalyzer.h"

AudioAnalyzer::AudioAnalyzer() {
    fft = arduinoFFT();
    samplingPeriodUS = (int) round(1000000 * (1.0 / samplingFrequency));
}

AudioAnalyzer::~AudioAnalyzer() = default;

void AudioAnalyzer::analyze() {
    sampling();

    fft.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
    fft.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
    fft.ComplexToMagnitude(vReal, vImag, samples);
    lastMajorPeak = fft.MajorPeak(vReal, samples, samplingFrequency);
    int tones = samples / 2;
    const int MINIMUM = 30; // @fixme

    for (int i = 2; i < tones; i++) {
        if (vReal[i] < MINIMUM) {
            vReal[i] = 0;
        }
    }

    // низкие частоты, выборка со 2 по 5 тон (0 и 1 зашумленные!)
    int lowEnd = 32;
    for (int i = 2; i < lowEnd; i++) {
        if (vReal[i] > low) {
            low = vReal[i];
        }
    }
    int midEnd = 96;
    for (int i = lowEnd; i < midEnd; i++) {
        if (vReal[i] > mid) {
            mid = vReal[i];
        }
    }
    for (int i = midEnd; i < samples; i++) {
        if (vReal[i] > high) {
            high = vReal[i];
        }
    }

    maxFrequency = max(low, max(mid, high));
    if (maxFrequency < 5) {
        maxFrequency = 5; // Why AlexGayver? Why?
    }
}

void AudioAnalyzer::sampling() {
    microseconds = micros();
    for (int i = 0; i < samples; i++) {
        vReal[i] = Application::getInstance().getAdc()->analogRead(0);
        if (vReal[i] < 650) { // @fixme remove hardcoded LOW_PASS_FILTER
            vReal[i] = 0;
        }
        vImag[i] = 0;
        while (micros() - microseconds < samplingPeriodUS) {
        }
        microseconds += samplingPeriodUS;
    };
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
