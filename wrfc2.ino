//
// water rocket flight computer mk2
// (c) 2022 icannotfly
//



#include "wrfc2.h"



// globals (eww, i know)
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);



void setup()
{
	// display
	initDisplay(&display);
	
	// barometer
	eBaroErrorCode baroInitCode = initDPS310();
	if (baroInitCode != eBaroErrorCode::NONE)
	{
		Serial.print("BARO ERROR");	// TODO lol please do something more useful than this, blink a LED or something sheesh
		while(1);
	}
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
	getBaroValues(&baroTemp, &baroPres);
	
	display.print("t: ");
	display.print(baroTemp);
	display.print(" C\n");

	display.print("p: ");
	display.print(baroPres);
	display.print(" hPa\n");

	display.print("a0: ");
	display.print(calcAltitude(baroPres, baroTemp));
	display.print(" m\n");

	display.print("a1: ");
	display.print(calcAltitude(baroPres, baroTemp, 1));
	display.print(" m\n");


	
	display.display();
	delay(250);
}
