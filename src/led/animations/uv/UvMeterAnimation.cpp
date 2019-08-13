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
#include "UvMeterAnimation.h"
DEFINE_GRADIENT_PALETTE(soundlevel_gp) {
        0,    0,    255,  0,  // green
        100,  255,  255,  0,  // yellow
        150,  255,  100,  0,  // orange
        200,  255,  50,   0,  // red
        255,  255,  0,    0   // red
};

void UvMeterAnimation::animate(CRGB *strip) {
    auto audioAnalyzer = Application::getInstance().getAudioAnalyzer();
    audioAnalyzer->analyzeLevels();

    float RsoundLevel_f = audioAnalyzer->RsoundLevel_f;
    float LsoundLevel_f = audioAnalyzer->LsoundLevel_f;

    CRGBPalette32 myPal = soundlevel_gp;

    if (EMPTY_BRIGHT > 5) {
        for (int i = 0; i < LED_LENGTH; i++)
            strip[i] = CHSV(HUE_PURPLE, 255, EMPTY_BRIGHT);
    }
    if (RsoundLevel_f > 15 && LsoundLevel_f > 15) {

        // расчёт общей средней громкости с обоих каналов, фильтрация.
        // Фильтр очень медленный, сделано специально для автогромкости
        averageLevel = (float) (RsoundLevel_f + LsoundLevel_f) / 2 * averK + averageLevel * (1 - averK);

        // принимаем максимальную громкость шкалы как среднюю, умноженную на некоторый коэффициент MAX_COEF
        maxLevel = (float) averageLevel * MAX_COEF;

        // преобразуем сигнал в длину ленты (где MAX_CH это половина количества светодиодов)
        Rlenght = map(RsoundLevel_f, 0, maxLevel, 0, MAX_CH);
        Llenght = map(LsoundLevel_f, 0, maxLevel, 0, MAX_CH);

        // ограничиваем до макс. числа светодиодов
        Rlenght = constrain(Rlenght, 0, MAX_CH);
        Llenght = constrain(Llenght, 0, MAX_CH);
    }

    count = 0;
    for (int i = (MAX_CH - 1); i > ((MAX_CH - 1) - Rlenght); i--) {
        strip[i] = ColorFromPalette(myPal, (count * index));   // заливка по палитре " от зелёного к красному"
        count++;
    }
    count = 0;
    for (int i = (MAX_CH); i < (MAX_CH + Llenght); i++) {
        strip[i] = ColorFromPalette(myPal, (count * index));   // заливка по палитре " от зелёного к красному"
        count++;
    }
    if (EMPTY_BRIGHT > 0) {
        CHSV this_dark = CHSV(HUE_PURPLE, 255, EMPTY_BRIGHT);
        for (int i = ((MAX_CH - 1) - Rlenght); i > 0; i--)
            strip[i] = this_dark;
        for (int i = MAX_CH + Llenght; i < LED_LENGTH; i++)
            strip[i] = this_dark;
    }
    FastLED.show();
}
