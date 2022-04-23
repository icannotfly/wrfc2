#include "craftinfo.h"
#include "Arduino.h"



CraftInfo::CraftInfo() : 
	currentAltitude_(DataPoint<float>(0, 0)),
	previousAltitude_(DataPoint<float>(0, 0)),
	ascentRate_(DataPoint<float>(0, 0))
{ }



bool CraftInfo::readyToLaunch()
{
	return bReadyToLaunch_;
}



void CraftInfo::setReadyToLaunch(bool bReadyToLaunch /*= true*/)
{
	bReadyToLaunch_ = bReadyToLaunch;
}



void CraftInfo::calcAscentRate()
{
	float deltaTime = currentAltitude_.time() - previousAltitude_.time();
	float deltaAlt = (previousAltitude_.time() == 0) ? 0.0 : deltaAlt = currentAltitude_.value() - previousAltitude_.value();

	ascentRate_ = DataPoint<float>(
		millis(),
		(deltaAlt / (deltaTime / 1000.0 /* ms to sec conversion */))
	);
}



float CraftInfo::currentAltitude()
{
	return currentAltitude_.value();
}



void CraftInfo::setAltitude(DataPoint<float> newAltitude)
{
	previousAltitude_ = currentAltitude_;
	currentAltitude_ = newAltitude;

	if (currentAltitude_.value() > maxAltitude_.value())
	{
		maxAltitude_ = currentAltitude_;
	}
	
	calcAscentRate();
}



float CraftInfo::ascentRate()
{
	return ascentRate_.value();
}



void CraftInfo::setGroundAltitude(float groundAltitude)
{
	groundAltitude_ = groundAltitude;
}



float CraftInfo::groundAltitude()
{
	return groundAltitude_;
}



DataPoint<float> CraftInfo::maxAltitude()
{
	return maxAltitude_;
}



DataPoint<float> CraftInfo::maxAltitudeAboveGround()
{
	return DataPoint<float>(
		maxAltitude_.time(),
		maxAltitude_.value() - groundAltitude_
	);
}
