#pragma once



template<typename T>
class DataPoint
{
private:
	unsigned long time_ = 0;
	T value_;

public:
	DataPoint();
	DataPoint(unsigned long time, T value);
	
	// returns the time, in ms, at which this data point was recorded
	unsigned long time();
	
	// returns the value at this point in time
	T value();
};
