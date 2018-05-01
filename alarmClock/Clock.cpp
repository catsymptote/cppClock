#include "stdafx.h"
#include "Clock.h"

#include <iostream>		// std::cout etc.
//#include <string>		// string for output
#include <stdlib.h>		// Clearing console screen
#include <thread>		// For threading
#include <chrono>		// Get time
#include <cwchar>		// Font size
#include <windows.h>	// Font size

using namespace std::chrono;

Clock::Clock()
{	
	this->second = 0;
	this->minute = 0;
	this->hour = 0;
	this->day = 0;
	this->year = 0;

	this->setTimeNow();
	this->clockLoop();
}

Clock::Clock(unsigned int year, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second)
{
	this->year = year;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
	
	this->clockLoop();
}

Clock::~Clock() {}


unsigned int Clock::getSecond() { return this->second; }
unsigned int Clock::getMinute() { return this->minute; }
unsigned int Clock::getHour() { return this->hour; }
unsigned int Clock::getDay() { return this->day; }
unsigned int Clock::getYear() { return this->year; }

void Clock::setSecond(unsigned int second) { if (second < 60) this->second = second; }
void Clock::setMinute(unsigned int minute){ if (minute < 60) this->minute = minute; }
void Clock::setHour(unsigned int hour) { if (hour < 60) this->hour = hour; }
void Clock::setDay(unsigned int day) { if (day < 60) this->day = day; }
void Clock::setYear(unsigned int year) { if (year< 60) this->year = year; }


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
	
	if (this->getTime() < this->ms + 1000)
		return false;
	//std::cout << ".";
	return true;
}

void Clock::clockLoop()
{
	this->ms = 0;
	this->displayClock = true;

	while (true)
	{
		if (this->updateNeeded())
		{
			this->ms = this->getTime();
			this->updateClock();
			if (this->displayClock)
			{
				this->displayTime();
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

	/// Formatting
	std::string time;
	

	std::cout << std::flush;
	system("CLS");
	std::cout << "yyyy" << ":" << "ddd" << " - " << "hh" << ":" << "mm" << ":" << "ss" << std::endl;
	//std::cout << year << "\t:" << day << "\t:" << hour << "\t:" << minute << "\t:" << second << std::endl;
	std::cout << this->formatTime() << std::endl;
	std::cout << this->getMonth() << std::endl;
	
	//std::cout << system_clock::now() << std::endl;
}

std::string Clock::formatTime()
{
	std::string time = "";

	/// Year
	if (this->year < 1000)
	{
		if (this->year < 100)
		{
			if (this->year < 10)
			{
				time += "0";
			}
			time += "0";
		}
		time += "0";
	}

	time += std::to_string(this->year);
	time += ":";

	/// Day
	if (this->day < 100)
	{
		if (this->year < 10)
		{
			time += "0";
		}
		time += "0";
	}

	time += std::to_string(this->day);
	time += " - ";

	/// Hour
	if (this->hour < 10)
	{
		time += "0";
	}

	time += std::to_string(this->hour);
	time += ":";

	/// Minute
	if (this->minute< 10)
	{
		time += "0";
	}

	time += std::to_string(this->minute);
	time += ":";
	
	/// Second
	if (this->second < 10)
	{
		time += "0";
	}

	time += std::to_string(this->second);

	return time;
}


/// Updates the numbers. Adds 1 second to time.
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
				unsigned int daysInYear = 365;
				if(this->leapYear)
					daysInYear = 366;

				if (this->day >= daysInYear - 1)
				{
					/// Years
					year++;
					if (this->isLeapYear())
						leapYear = true;
					else
						leapYear = false;
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

unsigned int Clock::getMonth()
{
	unsigned int d = this->day;

	/// January
	if (d <= 31)
		return 1;
	d -= 31;

	/// February
	unsigned int daysInFeb = 28;
	if (this->leapYear)
		daysInFeb = 29;
	if (d <= daysInFeb)
		return 2;
	d -= daysInFeb;
	
	/// March
	if (d <= 31)
		return 3;
	d -= 31;

	/// April
	if (d <= 30)
		return 4;
	d -= 30;

	/// May
	if (d <= 31)
		return 5;
	d -= 31;

	/// June
	if (d <= 30)
		return 6;
	d -= 30;

	/// July
	if (d <= 31)
		return 7;
	d -= 31;

	/// August
	if (d <= 31)
		return 8;
	d -= 31;

	/// September
	if (d <= 30)
		return 9;
	d -= 30;

	/// October
	if (d <= 31)
		return 10;
	d -= 31;

	/// November
	if (d <= 30)
		return 11;
	d -= 30;

	/// December
	if (d <= 31)
		return 12;
	
	std::cout << "Month error" << std::endl;
	return 0;
}


/// Add 1 second to the time per 1000 ms.
void Clock::setTimeNow()
{
	unsigned int now = this->getTime() / 1000;
	while (now > 0)
	{
		this->updateClock();
		now--;
	}
}

bool Clock::isLeapYear()
{
	unsigned int y = this->year;
	bool isLeap = false;

	if (y % 4 == 0)
		isLeap = true;
	if (y % 100)
		isLeap = false;
	if (y % 400)
		isLeap = true;

	return isLeap;
}
