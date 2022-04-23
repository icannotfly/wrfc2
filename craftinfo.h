#pragma once

#include "datapoint.h"



class CraftInfo
{
private:
	bool bReadyToLaunch_ = false;

	DataPoint<float> currentAltitude_;
	DataPoint<float> previousAltitude_;
	DataPoint<float> ascentRate_;

	// calculates the ascent rate. if no previous rate exists, rate will be set to 0.
	void calcAscentRate();

	float groundAltitude_;

	DataPoint<float> maxAltitude_;

public:
	CraftInfo();

	// are we done calibarating and so on?
	bool readyToLaunch();

	// informs the craft we're good to go. can be un-set. // TODO is there any reason to un-set this? // TODO is there a better way to handle this that doesn't involve the use of a throaway var like this? it's kinda wasteful RAM-wise.
	void setReadyToLaunch(bool bReadyToLaunch/* = true*/);

	// returns the craft's current altitude
	float currentAltitude();

	// sets the craft's current altitude. doing so will automatically calculate the ascent rate.
	void setAltitude(DataPoint<float> a);

	// returns the craft's current ascent rate in m/s
	float ascentRate();

	// sets the ground/starting altitude. takes a single value, does not do any averaging.
	void setGroundAltitude(float groundAltitude);

	// returns the estimated ground/starting altitude
	float groundAltitude();

	// returns the maximum altitude reached by this craft in m. note that this is the barometric altitude, not the total distance travelled by the craft
	DataPoint<float> maxAltitude();

	// returns the maximum distance between the ground and the craft
	DataPoint<float> maxAltitudeAboveGround();
};