#include "Arduino.h"
ADC_MODE(ADC_VCC);

#include "Application.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void setup() {
    delay(1);
    Application::getInstance().setup();
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void loop() {
    Application::getInstance().loop();
}
#pragma clang diagnostic pop


//#define SMOOTH_STEP 20
//#define LOW_COLOR HUE_RED         // цвет низких частот
//#define MID_COLOR HUE_GREEN       // цвет средних
//#define HIGH_COLOR HUE_BLUE     // цвет высоких
//byte EMPTY_BRIGHT = 30;
//int freq_max;
//float freq_max_f, rainbow_steps;
//float averK = 0.006;
//int colorMusic[3];
//float colorMusic_f[3], colorMusic_aver[3];
//float SMOOTH_FREQ = 0.8;          // коэффициент плавности анимации частот (по умолчанию 0.8)
//float MAX_COEF_FREQ = 1.2;
//int thisBright[3], strobe_bright = 0;
//boolean colorMusicFlash[3], strobeUp_flag, strobeDwn_flag;
//boolean running_flag[3];
//void audioLoop() {
//    audioAnalyzer->analyze();
//    double x = audioAnalyzer->getLastMajorPeak();
//    Serial.println(x);

//    colorMusic[0] = audioAnalyzer->getLowPercent();
//    colorMusic[1] = audioAnalyzer->getMidPercent();
//    colorMusic[2] = audioAnalyzer->getHighPercent();
//
//    freq_max_f = freq_max * averK + freq_max_f * (1 - averK);
//    for (byte i = 0; i < 3; i++) {
//        colorMusic_aver[i] = colorMusic[i] * averK + colorMusic_aver[i] * (1 - averK);  // общая фильтрация
//        colorMusic_f[i] = colorMusic[i] * SMOOTH_FREQ + colorMusic_f[i] * (1 - SMOOTH_FREQ);      // локальная
//        if (colorMusic_f[i] > ((float)colorMusic_aver[i] * MAX_COEF_FREQ)) {
//            thisBright[i] = 255;
//            colorMusicFlash[i] = true;
//            running_flag[i] = true;
//        } else colorMusicFlash[i] = false;
//        if (thisBright[i] >= 0) thisBright[i] -= SMOOTH_STEP;
//        if (thisBright[i] < EMPTY_BRIGHT) {
//            thisBright[i] = EMPTY_BRIGHT;
//            running_flag[i] = false;
//        }
//    }
//
//    for (int i = 0; i < NUM_LEDS; i++) {
//        if (i < NUM_LEDS / 3)          leds[i] = CHSV(HIGH_COLOR, 255, thisBright[2]);
//        else if (i < NUM_LEDS * 2 / 3) leds[i] = CHSV(MID_COLOR, 255, thisBright[1]);
//        else if (i < NUM_LEDS)         leds[i] = CHSV(LOW_COLOR, 255, thisBright[0]);
//    }
//    FastLED.show();
//}



