#ifndef G_SONAR_HC_SR04_H_
#define G_SONAR_HC_SR04_H_

#include "Arduino.h"
#include "utility/gSonar.h"

class HC_SR04 : public gSonar{

    public:
        HC_SR04(uint8_t, uint8_t);
        void begin();
        unsigned long raw();
    
    private:
        uint8_t _echo;
        uint8_t _triger;
};

#endif