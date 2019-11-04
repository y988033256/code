
#include "GameTimer.h"

GameTimer::GameTimer()
{
	if(QueryPerformanceFrequency(&freq)==0)		// Find the timer frequency
	{
		freq.QuadPart=0;									// Set to zero if function failed

	}

	mdGameRate = 1.0;                
                                      
                                    
	mdMinimumFrameTime=0;
	mdFrameTime = 0;
}


void GameTimer::mark()
{

	if (freq.QuadPart<=0)		// If frequency is zero (if QueryPerformanceCounter failed)
	{
		last.QuadPart=0;			// Set everything to zero. Something is badly wrong.
		mdFrameTime=0;
	}
	else
	{
		LARGE_INTEGER now;
		mdFrameTime=0.0;						      // Set to zero, ready for loop
		while(mdFrameTime<=mdMinimumFrameTime)	// This is a loop that causes a delay until minimum frame time has elapsed
                                             // Using "sleep" is just not accurate enough
		{

			QueryPerformanceCounter(&now);		// Get current time

			mdFrameTime=(now.QuadPart - last.QuadPart)/(double)freq.QuadPart;
											// Find time elapsed since last mark, and divide by
											// frequency to convert to seconds
		}

		mdFrameTime = mdFrameTime * mdGameRate;
		last=now;						// Update mark time with current time

	}
}



void GameTimer::setMinimumFrameTime(double minTime)
{
	if(minTime>0.0)      // Can't have a negative minimum time
	{
		mdMinimumFrameTime = minTime;
	}
	else 
		mdMinimumFrameTime=0.0;
}
