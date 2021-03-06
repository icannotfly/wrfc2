#include "dps310.h"



// the baro, the myth, the legend
Adafruit_DPS310 dps310;



void initDPS310()
{
	if (!dps310.begin_I2C(DPS310_I2CADDR_DEFAULT))
	{
		// TODO print to both screen and serial (and log?)
		Serial.println("Unable to contact barometer on 0x77.");
		return;
		//return ErrorCode::barometerCouldNotConnect;
	}

	// configure
	dps310.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
	dps310.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);
}



bool getBaroValues(float* temperature, float* pressure)
{
	if (!dps310.temperatureAvailable() || !dps310.pressureAvailable())
	{
		// TODO print to serial and to log, maybe to screen too
		return false;
	}

	sensors_event_t temperatureEvent;
	sensors_event_t pressureEvent;
	dps310.getEvents(&temperatureEvent, &pressureEvent);
	if (temperatureEvent.temperature == NAN || pressureEvent.pressure == NAN)
	{
		// TODO maybe print error?
		return false;
	}
	*temperature = temperatureEvent.temperature;
	*pressure = pressureEvent.pressure;
	return true;
}



float calcAltitude(float pressure, float temperature)
{
	return (pow((SEA_LEVEL_PRESSURE / pressure), 0.190223) - 1.0) * (temperature + 273.15) / 0.0065;
}



float calibrateGroundAltitude()
{
	Array<float, NUM_GROUND_ALT_READINGS_TO_TAKE> groundAltReadings;
	uint numGroundAltReadingsTaken = 0;

	float baroTemp;
	float baroPres;

	while (numGroundAltReadingsTaken < NUM_GROUND_ALT_READINGS_TO_TAKE)
	{
		if (getBaroValues(&baroTemp, &baroPres))
		{
			groundAltReadings[numGroundAltReadingsTaken] = calcAltitude(baroPres, baroTemp);
			numGroundAltReadingsTaken++;

			// TODO log readings to somewhere maybe
			// TODO log progress somewhere maybe
		}
	}

	float groundAlt = 0;
	for (uint i = 0; i < NUM_GROUND_ALT_READINGS_TO_TAKE; i++)
	{
		groundAlt += groundAltReadings[i];
	}
	groundAlt /= float(NUM_GROUND_ALT_READINGS_TO_TAKE);
	// TODO print result?

	return groundAlt;
}
