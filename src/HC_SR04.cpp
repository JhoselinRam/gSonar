#include "Arduino.h"
#include "HC_SR04.h"

//-------------- Constructor ------------------

/*
Set the initial values of the HC_SR04 class

Returns: no return.
*/
HC_SR04::HC_SR04(uint8_t triger, uint8_t echo){
    _triger = triger;
    _echo = echo;
    _lastTime = 0;
}

//---------------------------------------------
//----------------- Begin ---------------------

/*
Set the Arduino pins with the correct configuration

Returns: no return.
*/
void HC_SR04::begin(){
    
}

//---------------------------------------------