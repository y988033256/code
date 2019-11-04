


#pragma once

#include <windows.h>


class GameTimer
{
private:
	LARGE_INTEGER freq;		
	LARGE_INTEGER last;		
	double mdMinimumFrameTime;	
				

public:
	double mdFrameTime;		
	double mdGameRate;		
							    
	GameTimer();

		
	void setMinimumFrameTime(double minTime);
							

	void mark();			
						
};
