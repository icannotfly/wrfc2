#pragma once

//#include "wrfc2.h"
#include <Adafruit_DPS310.h>



#define DPS310_CS 10

#define SEA_LEVEL_PRESSURE 1013.25



// attempts to initialize the barometer
void initDPS310();

// if temperature and pressure values are available, fills passed values and returns true. returns false otherwise.
bool getBaroValues(float *temperature, float *pressure);

// converts the given pressure (in hPa) and temperature (in c) to altitude (in m)
float calcAltitude(float pressure, float temperature);
