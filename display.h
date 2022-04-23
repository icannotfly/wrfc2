#pragma once

#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>



// screen layout
#define OFFSET_LINE_1 0
#define OFFSET_LINE_2 8
#define OFFSET_LINE_3 16
#define OFFSET_LINE_4 24
#define OFFSET_LINE_5 32
#define OFFSET_LINE_6 40
#define OFFSET_LINE_7 48
#define OFFSET_LINE_8 56

#define OFFSET_STATE OFFSET_LINE_2
#define OFFSET_TEMP_PRES OFFSET_LINE_3
#define OFFSET_ALTITUDE OFFSET_LINE_4
#define OFFSET_DELTA_ALTITUDE OFFSET_LINE_5
#define OFFSET_MAX_ALT OFFSET_LINE_6
#define OFFSET_ASCENT_RATE OFFSET_LINE_7
#define OFFSET_DT OFFSET_LINE_8



// time, in ms, to display the splash logo on screen. set to =< 0 to disable splash
#define SPLASH_DISPLAY_TIME 2000

// initializes screen
void initDisplay(Adafruit_SH1107* display);

// clear everything and put the cursor back at 0. useful at the start of the main loop
void resetDisplay(Adafruit_SH1107* display);
