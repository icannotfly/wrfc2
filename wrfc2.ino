//
// water rocket flight computer mk2
// (c) 2022 icannotfly
//



#include "wrfc2.h"



// globals (eww, i know)
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);



void setup()
{
	// get things ready
	initDisplay(&display);
}



void loop()
{
	// reset the display
	resetDisplay(&display);

	display.print(VERSION);
	display.display();
}
