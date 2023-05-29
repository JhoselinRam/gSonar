#ifndef G_SONAR_DEFINITIONS_H_
#define G_SONAR_DEFINITIONS_H_

//------------ Macros ------------

//Temperature
#define cel2fah(c) (((c)*9.0/5)+32)    //From Celcius to Fahrenheit
#define cel2kel(c) ((c)+273.15)        //From Celcius to Kelvin
#define fah2cel(f) (((f)-32)*5.0/9)    //From Fahrenheit to Celcius
#define fah2kel(f) cel2kel(fah2cel(f)) //From Fahrenheit to Kelvin
#define kel2cel(k) ((k)-273.15)        //From Kelvin to Celcius
#define kel2fah(k) cel2fah(kel2cel(k)) //From Kelvin to Fahrenheit

//---------------------------------

//Default values
#define SONAR_DEFAULT_AIR_TEMPERATURE 20.0
#define SONAR_DEFAULT_SOUND_VELOCITY  0.34342

//Distance units
#define UNIT_DISTANCE_MM 0
#define UNIT_DISTANCE_CM 1
#define UNIT_DISTANCE_IN 2

//Temperature units
#define UNIT_TEMPERATURE_C 0
#define UNIT_TEMPERATURE_F 1
#define UNIT_TEMPERATURE_K 2

//Velocity units
#define UNIT_VELOCITY_MS   0
#define UNIT_VELOCITY_IS   1
#define UNIT_VELOCITY_KMPH 2
#define UNIT_VELOCITY_MPH  3

#endif