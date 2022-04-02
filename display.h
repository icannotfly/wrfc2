#ifndef DISPLAY_H
#define DISPLAY_H

#include "wrfc2.h"

#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>



// time, in ms, to display the splash logo on screen. set to =< 0 to disable splash.
#define SPLASH_DISPLAY_TIME 4000

// initializes screen. returns true if successful, false otherwise.
bool initDisplay(Adafruit_SH1107 * display);

// clear everything and put the cursor back at 0. useful at the start of the main loop
void resetDisplay(Adafruit_SH1107* display);



#endif 
