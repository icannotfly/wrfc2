#pragma once

#include <StateMachine.h>
#include "Arduino.h"



// init
void initStateMachine(StateMachine* sm);

// returns the human-readable name of the current state
String getCurrentStateName(StateMachine* sm);


// state definitions
void sdPreflightCalibration();
void sdWaitingToLaunch();
void sdAscent();
void sdDescentBallistic();
void sdDescentControlled();
void sdLanded();
void sdRecovered();



// state transition conditions
bool stCalibrationDone();
bool stLaunchDetected();
bool stApogeeDetected();
bool stChuteDeployDetected();
bool stImpactDetected();
bool stRecoveryDetected();
