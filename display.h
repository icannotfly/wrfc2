#pragma once

//#include "wrfc2.h"
#include <Adafruit_SH110X.h>    // already included in wrfc2.h
#include <Adafruit_GFX.h>



// screen layout:
// line	y-ofst	description	
// ----	----	----
// 1	0		version
// 2	8
// 3	16		temperature
// 4	24		pressure
// 5	32		altitude (method 0)
// 6	40		altitude (method 1)
// 7	48	
// 8	56		error

#define OFFSET_VERSION 0
#define OFFSET_LINE2 8
#define OFFSET_TEMPERATURE 16
#define OFFSET_PRESSURE 24
#define OFFSET_ALTITUDE0 32
#define OFFSET_ALTITUDE1 40
#define OFFSET_LINE7 48
#define OFFSET_ERROR 56



// time, in ms, to display the splash logo on screen. set to =< 0 to disable splash
#define SPLASH_DISPLAY_TIME 2000

// initializes screen
void initDisplay(Adafruit_SH1107* display);

// clear everything and put the cursor back at 0. useful at the start of the main loop
void resetDisplay(Adafruit_SH1107* display);
