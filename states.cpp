#include "states.h"
#include "craftinfo.h"

extern CraftInfo craft;



void initStateMachine(StateMachine* sm)
{
	State* sPreflightCalibration = sm->addState(sdPreflightCalibration);	// id 0
	State* sWaitingToLaunch = sm->addState(&sdWaitingToLaunch);				// id 1
	State* sAscent = sm->addState(&sdAscent);								// id 2
	State* sDescentBallistic = sm->addState(&sdDescentBallistic);			// id 3
	State* sDescentControlled = sm->addState(&sdDescentControlled);			// id 4
	State* sLanded = sm->addState(&sdLanded);								// id 5
	State* sRecovered = sm->addState(&sdRecovered);							// id 6
	// ids will be needed later

	sPreflightCalibration->addTransition(&stCalibrationDone, sWaitingToLaunch);
	sWaitingToLaunch->addTransition(&stLaunchDetected, sAscent);
	sAscent->addTransition(&stApogeeDetected, sDescentBallistic);
	sDescentBallistic->addTransition(&stChuteDeployDetected, sDescentControlled);
	sDescentBallistic->addTransition(&stImpactDetected, sLanded);
	sDescentControlled->addTransition(&stImpactDetected, sLanded);
	sLanded->addTransition(&stRecoveryDetected, sRecovered);
}



String getCurrentStateName(StateMachine* sm)
{
	switch (sm->currentState)
	{
		case -1:	return "INITIALIZING";
		case  0:	return "PREFLIGHT CALIBRATION";
		case  1:	return "WAITING TO LAUNCH";
		case  2:	return "ASCENT";
		case  3:	return "DESCENT BALLISTIC";
		case  4:	return "DESCENT CONTROLLED";
		case  5:	return "LANDED";
		case  6:	return "RECOVERED";
		default:	return "NOT SET";  break;
	}
}



void sdPreflightCalibration()
{
	// average out baro readings
}



void sdWaitingToLaunch()
{
	// turn light green
}



void sdAscent()
{
	// turn light off 
}



void sdDescentBallistic()
{

}



void sdDescentControlled()
{

}



void sdLanded()
{

}



void sdRecovered()
{

}



bool stCalibrationDone()
{
	return craft.readyToLaunch();
}



bool stLaunchDetected()
{
	return craft.ascentRate() >= 2.0;
}



bool stApogeeDetected()
{
	return false;
}



bool stChuteDeployDetected()
{
	return false;
}



bool stImpactDetected()
{
	return false;
}



bool stRecoveryDetected()
{
	return false;
}
