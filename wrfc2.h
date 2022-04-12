//
// water rocket flight computer mk2
// (c) 2022 icannotfly
//

#pragma once



// code version
#define VERSION "0.2.1"
#define BUILD "56"

#include <Wire.h>
#include <cmath>
#include <Adafruit_SH110X.h>

#include "display.h"	// screen
#include "dps310.h"		// barometer



void setup();
void loop();
