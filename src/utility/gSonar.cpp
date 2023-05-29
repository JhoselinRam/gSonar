/*
	gSonar library

	Author: Jhoselin Adrian Ramirez Montes
	Version:1.0.0
	Contact: jhoselin.ramirez92@gmail.com

	Description: This class provides an easy way to operate contactless ultrasonic distance
	sensors, such as hc-sr04 and hc-sr05. It include reads in centimeters, millimeters and inches, 
  implements temperature compensation and a filter to smooth the data, you can get the unfiltered
  raw data as well.

	Supported sensors:
	HC-SR04

  Units used internally:
  Time        -> microseconds (ms)
  Distance    -> millimeters (mm)
  Temperature -> celsius degrees (c)
  Velocity    -> millimeters per microsecond (mm/us)
*/


#include "Arduino.h"
#include "gSonar.h"
#include "../definitions.h"

//-------------- Constructor ------------------

/*
Description: Set the initial values of the base gSonar class.
Returns: No return.
*/
gSonar::gSonar(){
	_temperature = SONAR_DEFAULT_AIR_TEMPERATURE;
	_velocity = SONAR_DEFAULT_SOUND_VELOCITY;
	_distance     = 0;
	_lastTime = 0;
}

//---------------------------------------------
//----------------- Read ----------------------

/*
Performs a single read from the sensor and returns the distance measured in the 
specified unit.

read( unit )

unit(optional): A number representing the unit to be used 
The allowed values are: 
UNIT_DISTANCE_MM : millimeters.
UNIT_DISTANCE_CM : centimeters. 
UNIT_DISTANCE_IN : inches. 
Default : UNIT_DISTANCE_CM

Returns: A floating point number representing the distance measured.
*/
float gSonar::read(uint8_t unit){
	//Reads the raw data from the sensor
	unsigned long data = raw(); // us
	float distance = _velocity*data/2; //mm
	
	//Returns the result in the specified unit
	switch (unit){
		case UNIT_DISTANCE_MM:
			return distance;
		
		case UNIT_DISTANCE_CM:
			return distance * 0.1;

		case UNIT_DISTANCE_IN:
			return distance * 0.03937;
		
		default:
			return distance;
	}
}

//---------------------------------------------
//------------- Filter Read -------------------

/*
Performs a single read from the sensor and returns the filtered 
distance in the specified unit.

filterRead( unit )

unit(optional): A number representing the unit to be used 
The allowed values are: 
UNIT_DISTANCE_MM : millimeters.
UNIT_DISTANCE_CM : centimeters. 
UNIT_DISTANCE_IN : inches. 
Default : UNIT_DISTANCE_CM

Returns: A floating point number representing the distance measured.

Note: For the filter to work properly, this method needs to be called 
constantly with little time between call.

This method is suitable if you are going to constantly measure the distance,
to avoid an obstacle, for example.
But if you're planning to measure the distance only when certain condition is meet,
like a button pulse, it is best to use the read() method.
*/
float gSonar::filterRead(uint8_t unit){
	//Reads the raw data from the sensor
	unsigned long data = raw(); // us
	float rawDistance = _velocity*data/2; //mm

	//Apply the filter
	_distance += _gain*(rawDistance - _distance);
	
	//Returns the result in the specified unit
	switch (unit){
		case UNIT_DISTANCE_MM:
			return _distance;
		
		case UNIT_DISTANCE_CM:
			return _distance * 0.1;

		case UNIT_DISTANCE_IN:
			return _distance * 0.03937;
		
		default:
			return _distance;
	}
}

//---------------------------------------------
//------------ Air Temperature ----------------

/*
Change the value of the air temperature, this value is used to calculate the velocity
of sound in air. So changing this values will also change the velocity value.

airTemperature( temperature, unit )

temperature: A floating point number representing the air temperature 
in the specified units

unit(optional): A number representing the unit to be used 
The allowed values are: 
UNIT_TEMPERATURE_C : Celcius.
UNIT_TEMPERATURE_F : Fahrenheit.
UNIT_TEMPERATURE_K : Kelvin.
Default : UNIT_TEMPERATURE_C

Returns: No return.
*/
void gSonar::airTemperature(float temperature, uint8_t unit = UNIT_TEMPERATURE_C){
	
	//Transform the temperature to celcius
	switch(unit){
		case UNIT_TEMPERATURE_C:
			_temperature = temperature;
			break;

		case UNIT_TEMPERATURE_F:
			_temperature = fah2cel(temperature);
			break;

		case UNIT_TEMPERATURE_K:
			_temperature = kel2cel(temperature);
			break;

		default:
			_temperature = temperature;
			break;
	}
	
	//Updates the velocity
	_velocity = (331.3+0.606*_temperature)/1000.0;  //Velocity in mm/us
}



/*
Gets the value of the air temperature in the specified unit.

airTemperature( unit )

unit(optional): A number representing the unit to be used 
The allowed values are: 
UNIT_TEMPERATURE_C : Celcius.
UNIT_TEMPERATURE_F : Fahrenheit.
UNIT_TEMPERATURE_K : Kelvin.
Default : UNIT_TEMPERATURE_C

Returns: A floating point number representing the temperature of air
in the specified units.
*/
float gSonar::airTemperature(uint8_t unit = UNIT_TEMPERATURE_C){	
	switch(unit){
		case UNIT_TEMPERATURE_C:
			return _temperature;

		case UNIT_TEMPERATURE_F:
			return cel2fah(_temperature);

		case UNIT_TEMPERATURE_K:
			return cel2kel(_temperature);

		default:
			return _temperature;
	}
}