//
// Created by Андрей Клюев on 2019-07-31.
//

#include "ExternalADC.h"

int ExternalADC::analogRead(int channel) {
    return mcp3208.readADC(channel);
}
