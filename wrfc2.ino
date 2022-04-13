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
#include "display.h"	// screen
#include "states.h"		// state machine
#include "dps310.h"		// barometer



void setup()
{
	// display
	initDisplay(&display);
	
	// barometer
	initDPS310();
}



void loop()
{
	// reset the display
	resetDisplay(&display);

	display.print("wrfc2 ");
	display.print(VERSION);
	display.print(" build ");
	display.print(BUILD);
	display.print("\n\n");
	


	float baroTemp;
	float baroPres;



	display.setCursor(0, OFFSET_TEMPERATURE);
	display.print("t: ");

	display.setCursor(0, OFFSET_PRESSURE);
	display.print("p: ");

	display.setCursor(0, OFFSET_ALTITUDE0);
	display.print("a0: ");

	display.setCursor(0, OFFSET_ALTITUDE1);
	display.print("a1: ");



	if (getBaroValues(&baroTemp, &baroPres))
	{
		display.setCursor(24, OFFSET_TEMPERATURE);
		display.print(baroTemp);
		display.print(" C");

		display.setCursor(24, OFFSET_PRESSURE);
		display.print(baroPres);
		display.print(" hPa");

		display.setCursor(24, OFFSET_ALTITUDE0);
		display.print(calcAltitude(baroPres, baroTemp));
		display.print(" m");

		display.setCursor(24, OFFSET_ALTITUDE1);
		display.print(calcAltitude(baroPres, baroTemp, 1));
		display.print(" m");
	}



	display.display();
	delay(100);
}
