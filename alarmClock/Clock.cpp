#include "stdafx.h"
#include "Clock.h"

#include <iostream>		// std::cout etc.
#include <stdlib.h>		// Clearing console screen
#include <chrono>		// Get time


Clock::Clock()
{	
	this->second = 0;
	this->minute = 0;
	this->hour = 0;
	this->day = 1;
	this->year = 0;

	this->month = 1;
	this->dayOfMonth = 1;
	this->timeZone = 2;

	this->ms = 0;
	this->setTimeNow();
	this->clockLoop();
}

Clock::Clock(long long int year, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second)
{
	this->year = year;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;

	this->month = 1;
	this->dayOfMonth = 1;
	this->timeZone = 2;
	
	this->ms = 0;
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
void Clock::setHour(unsigned int hour) { if (hour < 24) this->hour = hour; }
void Clock::setDay(unsigned int day) { if (day < 366 && day > 0) this->day = day; }
void Clock::setYear(unsigned int year) { this->year = year; }


/// Main clock loop.
void Clock::clockLoop()
{
	this->displayClock = true;

	while (true)
	{
		if (this->updateNeeded())
		{
			this->ms = this->getms();
			this->updateClock();
			if (this->displayClock)
			{
				this->displayTime();
			}
		}
	}
}

/// Return (milli)seconds since epoch (1970).
unsigned long long int Clock::getms()
{
	std::chrono::milliseconds millisec = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);
	unsigned long long int ms = (unsigned long long int)millisec.count();// +150000000;

	ms = ms + timeZone * 3600000;
	return ms;
}

/// Check if clock needs an update (if 1 second has passed since last).
bool Clock::updateNeeded()
{
	if (this->getms() <= this->ms + 1000)
		return false;
	return true;
}

/// Display the time.
void Clock::displayTime()
{
	/// Flush and clear screen.
	system("CLS");

	/// cout the time/date.
	this->month = this->getMonthSetDay();
	std::string currentMonth = this->getMonthName(this->month);
	
	std::cout << "yyyy" << ":" << "mm" << ":" << "dd"<< " - "
		<< "hh" << ":" << "mm" << ":" << "ss" << std::endl;
	std::cout << this->getFormatTime() << std::endl;
	std::cout << currentMonth << std::endl;
	std::cout << this->getms() << std::endl;
}

/// Get the formatted time.
std::string Clock::getFormatTime()
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

	/// Month
	if (this->month < 10)
	{
		time += "0";
	}

	time += std::to_string(this->month);
	time += ":";

	/// Day
	if (this->dayOfMonth < 10)
	{
		time += "0";
	}
	
	time += std::to_string(this->dayOfMonth);
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
					daysInYear++;

				if (this->day >= daysInYear - 0)
				{
					/// Years
					this->year++;
					if (this->isLeapYear())
						this->leapYear = true;
					else
						this->leapYear = false;
					this->day = 1;
					this->hour = 0;
					this->minute = 0;
					this->second = 0;
					return;
				}
				this->day++;
				this->hour = 0;
				this->minute = 0;
				this->second = 0;
				return;
			}
			this->hour++;
			this->minute = 0;
			this->second = 0;
			return;
		}
		this->minute++;
		this->second = 0;
		return;
	}
	this->second++;
	return;
}

/// Get the month number and set the day of the month.
unsigned int Clock::getMonthSetDay()
{
	unsigned int d = this->day;

	/// January
	if (d <= 31)
	{
		this->dayOfMonth = d;
		return 1;
	}
	d -= 31;

	/// February
	unsigned int daysInFeb = 28;
	if (this->leapYear)
		daysInFeb = 29;
	if (d <= daysInFeb)
	{
		this->dayOfMonth = d;
		std::cout << this->dayOfMonth << std::endl;
		return 2;
	}
	d -= daysInFeb;
	
	/// March
	if (d <= 31)
	{
		this->dayOfMonth = d;
		return 3;
	}
	d -= 31;

	/// April
	if (d <= 30)
	{
		this->dayOfMonth = d;
		return 4;
	}
	d -= 30;

	/// May
	if (d <= 31)
	{
		this->dayOfMonth = d;
		return 5;
	}
	d -= 31;

	/// June
	if (d <= 30)
	{
		this->dayOfMonth = d;
		return 6;
	}
	d -= 30;

	/// July
	if (d <= 31)
	{
		this->dayOfMonth = d;
		return 7;
	}
	d -= 31;

	/// August
	if (d <= 31)
	{
		this->dayOfMonth = d;
		return 8;
	}
	d -= 31;

	/// September
	if (d <= 30)
	{
		this->dayOfMonth = d;
		return 9;
	}
	d -= 30;

	/// October
	if (d <= 31)
	{
		this->dayOfMonth = d;
		return 10;
	}
	d -= 31;

	/// November
	if (d <= 30)
	{
		this->dayOfMonth = d;
		return 11;
	}
	d -= 30;

	/// December
	if (d <= 31)
	{
		this->dayOfMonth = d;
		return 12;
	}
	
	std::cout << "Month error" << std::endl;
	return 0;
}

/// Get name of month by month number.
std::string Clock::getMonthName(unsigned int monthNum)
{
	switch (monthNum)
	{
		case 1:
			return "January";
		case 2:
			return "February";
		case 3:
			return "March";
		case 4:
			return "April";
		case 5:
			return "May";
		case 6:
			return "June";
		case 7:
			return "July";
		case 8:
			return "August";
		case 9:
			return "September";
		case 10:
			return "October";
		case 11:
			return "November";
		case 12:
			return "December";
		default:
			return "Month not found!";
	}
}

/// Add 1 second to the time per 1000 ms. (really slow atm due to Clock::updateTime() being ineffective when more than 1 second is added at a time.
void Clock::setTimeNow()
{
	std::cout << "Started time setting" << std::endl;
	this->year = 1970;
	unsigned long long int secondsFromEpoch = this->getms() / 1000;
	unsigned long long int epochToStart = secondsFromEpoch;

	int perCount = 1;
	while (secondsFromEpoch > 0)
	{
		/// Display how far in the time set process it has come.
		if ((epochToStart - secondsFromEpoch) > 5*perCount*0.01*epochToStart)
		{
			std::cout << 5*perCount << "%" << std::endl;
			perCount++;
		}
			
		this->updateClock();
		secondsFromEpoch--;
	}
}

/// Return true if the year is a leap year.
bool Clock::isLeapYear()
{
	unsigned int y = this->year;
	bool isLeap = false;

	if (y % 4 == 0)
		isLeap = true;
	if (y % 100 == 0 && y % 400 != 0)
		isLeap = false;

	return isLeap;
}
