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



