#ifndef DPS310_H
#define DPS310_H

#include <Adafruit_DPS310.h>



#define DPS310_CS 10

#define SEA_LEVEL_PRESSURE 1013.25



// 
enum eBaroErrorCode
{
	// reserved
	NONE = 0,				// no error
	
	// 1_, connection related
	connectionError = 10,	// nonspecific connection error
	couldNotConnect = 11,	// unable to connect at init (*never* able to connect)
	lostConnection	= 12,	// unable to connect after init (connected earlier, but can't connect now)

	// 2_, sensor value related
	sensorValueError = 20,	// nonspecific sensor value error
	noValuesReported = 21,	// expected a value, but got nothing. make sure the board has been initialized.
	noValuesAvailable = 22	// no fresh values are available.
};



// attempts to initialize the barometer. returns 0 if successful. otherwise, returns an eBaroErrorCode describing the failure. it is up to the user to halt or not on failure.
eBaroErrorCode initDPS310();

// if temperature and pressure values are available, fills passed values and returns eBaroErrorCode::NONE. returns error code otherwise.
eBaroErrorCode getBaroValues(float *temperature, float *pressure);

// converts the given pressure (in hPa) and temperature (in c) to altitude (in m) using the (optionally) specified method (0 = some random shit i found on the arduino forums, 1 = some random shit i found on some rando's webpage)
float calcAltitude(float pressure, float temperature, uint method = 0);


#endif
