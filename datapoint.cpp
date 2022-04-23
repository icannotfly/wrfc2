#include "datapoint.h"



//// float
template<> DataPoint<float>::DataPoint()								: time_(0),		value_(0)		{ }
template<> DataPoint<float>::DataPoint(unsigned long time, float value)	: time_(time),	value_(value)	{ }

template<> unsigned long	DataPoint<float>::time()	{ return time_; }
template<> float			DataPoint<float>::value()	{ return value_; }



//// int	// TODO (?)
