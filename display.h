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

/*
  +---------1----------2
1 |  wrfc2 0.3.0 b 100		version, build
2 |01: WAITING TO LAUNCH	state number, state name
3 |28.04 C   1012.90 hPa	temp, pressure
4 |current   __2.34 m		current alt
5 |max       _52.51 m		max alt
6 |ground    __2.01 m		ground alt
7 |v rate   +__2.45 m/s		ascent rate
8 |
*/
#define OFFSET_STATE OFFSET_LINE_2
#define OFFSET_TEMP_PRES OFFSET_LINE_3
#define OFFSET_CURRENT_ALTITUDE OFFSET_LINE_4
#define OFFSET_MAX_ALTITUDE OFFSET_LINE_5
#define OFFSET_GROUND_ALTITUDE OFFSET_LINE_6
#define OFFSET_ASCENT_RATE OFFSET_LINE_7



// time, in ms, to display the splash logo on screen. set to =< 0 to disable splash
#define SPLASH_DISPLAY_TIME 2000

// initializes screen
void initDisplay(Adafruit_SH1107* display);

// clear everything and put the cursor back at 0. useful at the start of the main loop
void resetDisplay(Adafruit_SH1107* display);
