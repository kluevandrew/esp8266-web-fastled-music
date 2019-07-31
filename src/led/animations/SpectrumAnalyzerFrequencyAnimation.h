//
// Created by Андрей Клюев on 2019-08-01.
//

#ifndef ESP8266_WEB_FASTLED_MUSIC_SPECTRUMANALYZERFREQUENCYANIMATION_H
#define ESP8266_WEB_FASTLED_MUSIC_SPECTRUMANALYZERFREQUENCYANIMATION_H

#include <config/config.h>
#include "FrequencyAnimation.h"

class SpectrumAnalyzerFrequencyAnimation : public FrequencyAnimation {
public:
    SpectrumAnalyzerFrequencyAnimation() = default;

    explicit SpectrumAnalyzerFrequencyAnimation(const JsonObject &options);

    ~SpectrumAnalyzerFrequencyAnimation() override = default;

    void animate() override;

private:
    uint8_t startColor = 0;
    uint8_t step = 5;
    uint8_t smooth = 2;
    double frequencies[ADC_SAMPLES / 2]{};
};


#endif //ESP8266_WEB_FASTLED_MUSIC_SPECTRUMANALYZERFREQUENCYANIMATION_H
