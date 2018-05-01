#include "stdafx.h"
#include "Clock.h"

#include <iostream>		// std::cout etc.
#include <stdlib.h>		// Clearing console screen
#include <thread>		// For threading
#include <chrono>		// Get time
#include <cwchar>		// Font size
#include <windows.h>	// Font size

using namespace std::chrono;

Clock::Clock()
{	
	this->ms = 0;
	this->displayClock = true;
	this->second = 0;
	this->minute = 0;
	this->hour = 0;
	this->day = 0;
	this->week = 0;
	this->month = 0;
	this->year = 0;

	//std::thread clkMain(clock::clockLoop);
	Clock::clockLoop();
}

Clock::~Clock() {}


unsigned int Clock::getTime()
{
	milliseconds millisec = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);
	unsigned int ms = (unsigned int)millisec.count();
	return ms;
}

bool Clock::updateNeeded()
{
	
	if (Clock::getTime() < this->ms + 1000)
		return false;
	//std::cout << ".";
	return true;
}

void Clock::clockLoop()
{
	while (true)
	{
		if (Clock::updateNeeded())
		{
			this->ms = Clock::getTime();
			Clock::updateClock();
			if (Clock::displayClock)
			{
				Clock::displayTime();
			}
		}

		/*
		/// For testing purposes.
		if (this->second > 5)
			return;
		*/
	}
}

//unsigned int displayIgnore = 0;
void Clock::displayTime()
{
	
	/*
	/// For testing purposes.
	displayIgnore++;
	if (displayIgnore % 1 != 0)
		return;
	*/

	std::cout << std::flush;
	system("CLS");
	std::cout << "year" << "\t: " << "day" << "\t: " << "hour" << "\t: " << "min" << "\t: " << "sec" << std::endl;
	std::cout << year << "\t: " << day << "\t: " << hour << "\t: " << minute << "\t: " << second << std::endl;
	//std::cout << this->ms << std::endl;
}


/// Updates the numbers. Ran once every second.
void Clock::updateClock()
{
	/// Seconds
	if (this->second >= 60 - 1)
	{
		/// Minutes
		if (this->minute >= 60 - 1)
		{
			/// Hours
			if (this->hour >= 24 - 1)
			{
				/// Days
				if (this->day >= 365 - 1)
				{
					/// Years
					year++;
					day = 0;
					return;
				}
				day++;
				hour = 0;
				return;
			}
			hour++;
			minute = 0;
			return;
		}
		minute++;
		second = 0;
		return;
	}
	second++;
	return;
}