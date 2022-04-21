#pragma once

#include "datapoint.h"



class CraftInfo
{
private:
	DataPoint<float> currentAltitude_;
	DataPoint<float> previousAltitude_;
	DataPoint<float> ascentRate_;

	// calculates the ascent rate. if no previous rate exists, rate will be set to 0.
	void calcAscentRate();

public:
	CraftInfo();

	// returns the craft's current altitude
	float currentAltitude();

	// sets the craft's current altitude. doing so will automatically calculate the ascent rate.
	void setAltitude(DataPoint<float> a);

	// returns the craft's current ascent rate in m/s
	float ascentRate();
};