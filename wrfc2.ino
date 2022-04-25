//
// water rocket flight computer mk2
// (c) 2022 icannotfly
//



#include <Arduino.h>
#include <Wire.h>
#include <cmath>
#include <Adafruit_SH110X.h>
#include <StateMachine.h>

#include "wrfc2.h"		// main
#include "craftinfo.h"	// craft
#include "display.h"	// screen
#include "states.h"		// state machine
#include "dps310.h"		// barometer



//// globals

// not sure how to describe this... logical deliniation?
CraftInfo craft;

// hardware
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
StateMachine sm = StateMachine();

// time
unsigned long deltaTime = 0;
unsigned long lastMillis = 0;



void setup()
{
	// display
	initDisplay(&display);

	// state machine
	initStateMachine(&sm);
	
	// barometer
	initDPS310();



	// done with rudimentary setup
	resetDisplay(&display);
	display.setCursor(0, 0);
	display.print("Calibrating...");
	display.display();

	// determine what the ground altitude is
	craft.setGroundAltitude(calibrateGroundAltitude());	// TODO pass the number of samples in as a param

	// good to go
	craft.setReadyToLaunch(true);
	display.print("done!");
	display.display();
}



void loop()
{
	// update dt
	deltaTime = millis() - lastMillis;
	lastMillis = millis();


	// get readings from sensors
	float baroTemp;
	float baroPres;

	bool bBaroValuesUpdated = getBaroValues(&baroTemp, &baroPres);
	if (bBaroValuesUpdated)
	{
		// use sensor data to update craft state
		craft.setAltitude(DataPoint<float>(millis(), calcAltitude(baroPres, baroTemp)));
	}



	// run the state machine
	sm.run();



	//// log things to the screen

	// reset the display
	resetDisplay(&display);

	// first line info
	display.print("  wrfc2 ");
	display.print(VERSION);
	display.print(" b ");
	display.print(BUILD);

	// remaining static line headers
	display.setCursor(0, OFFSET_STATE);
	if (sm.currentState < 10) // ghetto padding
	{
		display.print("s");
	}
	display.print(sm.currentState);
	display.print(": ");
	display.print(getCurrentStateName(&sm));

	display.setCursor((6 * 6), OFFSET_TEMP_PRES);
	display.print("C");
	display.setCursor((18 * 6), OFFSET_TEMP_PRES);
	display.print("hPa");

	display.setCursor(0, OFFSET_CURRENT_ALTITUDE);
	display.print("current          m");

	display.setCursor(0, OFFSET_MAX_ALTITUDE);
	display.print("max              m");
	
	display.setCursor(0, OFFSET_GROUND_ALTITUDE);
	display.print("ground           m");
	
	display.setCursor(0, OFFSET_ASCENT_RATE);
	display.print("v rate           m/s");



	// info that will be updated if values have been changed. otherwise, leave them be
	if (bBaroValuesUpdated)
	{
		display.setCursor(0, OFFSET_TEMP_PRES);
		display.print(baroTemp);
		display.setCursor((10 * 6), OFFSET_TEMP_PRES);
		display.print(baroPres);

		display.setCursor((((craft.currentAltitude() >= 10) ? 10 : 11) * 6), OFFSET_CURRENT_ALTITUDE);
		display.print(craft.currentAltitude());

		display.setCursor((((craft.maxAltitude().value() >= 10) ? 10 : 11) * 6), OFFSET_MAX_ALTITUDE);
		display.print(craft.maxAltitude().value());

		display.setCursor((((craft.groundAltitude() >= 10) ? 10 : 11) * 6), OFFSET_GROUND_ALTITUDE);
		display.print(craft.groundAltitude());

		display.setCursor((((craft.ascentRate() >= 10) ? 10 : 11) * 6), OFFSET_ASCENT_RATE);
		display.print(abs(craft.ascentRate()));
		display.setCursor((9 * 6), OFFSET_ASCENT_RATE);
		display.print(craft.ascentRate() > 0 ? "+" : "-");

		// only draw if there are updates to draw, otherwise it will flicker
		display.display();
	}



	delay(250);
}
