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

// distance/rate
//float groundAltitude = 0;	// the measured ground/starting altitude, in m
//float maxAltitude = -100;	// maximum altitude, in m, reached during this flight
//float currentAltitude = 0;	// current altitude, in m
//float lastAltitude = 0;		// the last measured altitude, in m
//float ascentRate = 0;		// rate, in m/s, in which we are ascending

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
	display.print("wrfc2 ");
	display.print(VERSION);
	display.print(" build ");
	display.print(BUILD);
	display.print("\n\n");

	// remaining line headers
	display.setCursor(0, OFFSET_STATE);
	display.print("state ");
	display.print(sm.currentState);

	display.setCursor(0, OFFSET_ALTITUDE);
	display.print("a: ");

	display.setCursor(0, OFFSET_DELTA_ALTITUDE);
	display.print("da: ");

	display.setCursor(0, OFFSET_MAX_ALT);
	display.print("max alt: ");

	display.setCursor(0, OFFSET_ASCENT_RATE);
	display.print("ar: ");

	display.setCursor(0, OFFSET_DT);
	display.print("dt: ");



	// info that will be updated if values have been changed. otherwise, leave them be
	if (bBaroValuesUpdated)
	{
		display.setCursor(0, OFFSET_TEMP_PRES);
		display.print(baroTemp);
		display.print("C  ");
		display.print(baroPres);
		display.print("hPa");

		display.setCursor((3*6), OFFSET_ALTITUDE);
		display.print(craft.currentAltitude());
		display.print("m");

		display.setCursor((3*6), OFFSET_DELTA_ALTITUDE);
		display.print(craft.currentAltitude() - craft.groundAltitude());
		display.print("m");

		display.setCursor((9*6), OFFSET_MAX_ALT);
		display.print(craft.maxAltitude());
		display.print("m");

		display.setCursor((4 * 6), OFFSET_ASCENT_RATE);
		display.print(craft.ascentRate());
		display.print("m/s");

		display.setCursor((4 * 6), OFFSET_DT);
		display.print(deltaTime);
		display.print("ms");
		
		// only draw if there are updates to draw, otherwise it will flicker
		display.display();
	}



	delay(250);
}
