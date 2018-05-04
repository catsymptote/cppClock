#include "stdafx.h"
#include "Clock.h"

#include <iostream>		// For std::cout and std::endl
#include <stdlib.h>		// Clearing console screen
#include <chrono>		// Get time


Clock::Clock()
{	
	this->second = 0;
	this->minute = 0;
	this->hour = 0;
	this->day = 0;
	this->year = 0;

	this->month = 1;
	this->weekOfYear = 1;
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
	this->weekOfYear = 1;
	this->dayOfMonth = 1;
	this->timeZone = 2;
	
	this->ms = 0;
	this->clockLoop();
}

Clock::~Clock() {}


/// Main clock loop.
void Clock::clockLoop()
{
	this->displayClock = true;

	while (true)
	{
		if (this->updateNeeded())
		{
			this->ms = this->getms();
			this->updateClock(1);
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
	/// Get milliseconds since epoch.
	std::chrono::milliseconds millisec = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	);
	unsigned long long int ms = (unsigned long long int)millisec.count();

	/// Add timeZone changer, add 2 days (because reasons) and leap seconds.
	if (firstGetms)
	{
		this->firstGetms = false;
		this->leapSec = this->leapSecondAdder(ms);
		std::cout << "leapSeconds: " << this->leapSec << std::endl;
	}
	ms += (timeZone * this->secPerHour + 2 * this->secPerDay - this->leapSec) * this->msPerSec;
	this->ms = ms;
	return ms;
}

/// Check if clock needs an update (if 1 second has passed since last).
bool Clock::updateNeeded()
{
	bool needUpdate = true;
	unsigned int thisMsMod = this->getms() % 1000;
	if (thisMsMod < this->lastMsMod)
		return false;
	this->lastMsMod = thisMsMod;
	return needUpdate;
}

/// Display the time.
void Clock::displayTime()
{
	/// Flush and clear screen.
	system("CLS");

	/// cout the time/date.
	std::cout << this->getFormatTime() << std::endl;

	this->month = this->getMonthSetDay();
	std::cout << this->getFormatTimeAsText1() << std::endl;
	//std::cout << this->getFormatTimeAsText2() << std::endl;
	
	std::cout << "ms since epoch:\t" << this->getms() << std::endl;
}

/// Get the formatted time.
std::string Clock::getFormatTime()
{
	std::string time = "\nyyyy:mm:dd - hh:mm:ss\n";

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
	time += "\n";

	return time;
}

/// Display the time as text v1.
std::string Clock::getFormatTimeAsText1()
{
	std::string text = this->getMonthName(this->month) + " " +	// month
		std::to_string(this->dayOfMonth) +						// day of month
		this->getDayExtension(this->dayOfMonth) + ", " +		// day extension
		std::to_string(this->year) + "\n";						// year

	return text;
}

/// Display the time as text v2.
std::string Clock::getFormatTimeAsText2()
{
	std::string text = this->getWeekdayName(this->getWeekdayNumber()) + ", the " +	// weekday
		std::to_string(this->dayOfMonth) +						// day of month
		this->getDayExtension(this->dayOfMonth) + " of " +		// day extension
		this->getMonthName(this->month)							// month
		+ ", in the year " + std::to_string(this->year) + "\n";	// year

	return text;
}

/// Updates the numbers. Adds 1 second to time.
void Clock::updateClock(unsigned int sec)
{
	/// Add entire days at a time.
	if (sec == this->secPerDay)
	{
		this->incrementDay();
		return;
	}
	
	/// Recursion (because reasons).
	if (!(sec == this->secPerDay || sec == 1))
	{
		updateClock(1);
		sec--;
		return;
	}
	
	/// Indicidual increments.
	/// Seconds
	if (this->second >= this->secPerMin - 1)
	{
		/// Minutes
		if (this->minute >= this->minPerHour - 1)
		{
			/// Hours
			if (this->hour >= this->hourPerDay - 1)
			{
				this->incrementDay();
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

/// Add a day to the year.
void Clock::incrementDay()
{
	/// Leap year check
	unsigned int daysInYear = this->dayPerYear;
	if (this->leapYear)
		daysInYear++;

	/// If a year has passed
	if (this->day >= daysInYear - 0)
	{
		/// Increment year
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
		daysInFeb++;
	if (d <= daysInFeb)
	{
		this->dayOfMonth = d;
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
	
	std::cout << "[Error! Month not found]" << std::endl;
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
			return "[Month not found]";
	}
}

/// Get week number (1 - 52/53)
unsigned int Clock::getWeekNumber()
{
	/// Works only when the first day of the year is a Monday.
	unsigned int currentWeekday = this->getWeekdayNumber();
	unsigned int weekNumber = (unsigned int)((this->day - currentWeekday) / 7 + 1);
	return weekNumber;
}

/// Get weekday number (1, 2, ..)
unsigned int Clock::getWeekdayNumber()
{
	unsigned int daysSinceEpoch = this->ms / (this->msPerSec * this->secPerDay);
	return ((daysSinceEpoch +1) % 7) + 1;
}

/// Get weekday name (Monday, Tuesday, ..).
std::string Clock::getWeekdayName(unsigned int weekday)
{
	switch (weekday)
	{
		case 1:
			return "Monday";
		case 2:
			return "Tuesday";
		case 3:
			return "Wednesday";
		case 4:
			return "Thursday";
		case 5:
			return "Friday";
		case 6:
			return "Saturday";
		case 7:
			return "Sunday";
		default:
			return "[Weekday not found]";
	}
}

/// Get text extension to day (st, nd, th).
std::string Clock::getDayExtension(unsigned int day)
{
	if (day % 10 == 1)
		return "st";
	else if (day % 10 == 2)
		return "nd";
	else if (day % 10 == 3)
		return "rd";
	else
		return "th";
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
		if ((epochToStart - secondsFromEpoch) > 10*perCount*0.01*epochToStart)
		{
			std::cout << 10*perCount << "%" << std::endl;
			perCount++;
		}
		
		/// If more than 1 day, send entire day at once.
		if (secondsFromEpoch >= this->secPerDay)
		{
			this->updateClock(this->secPerDay);
			secondsFromEpoch -= this->secPerDay;
		}
		/// If less than 1 day, send second by second.
		else
		{
			this->updateClock(1);
			secondsFromEpoch--;
		}
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

/// Handles adding leap seconds and conversion between NTP time and UNIX Epoch time.
int Clock::leapSecondAdder(unsigned long long int ms)
{
	/// Assumes only positive (additive) leap seconds, not negative (subtractive).
	const unsigned int NTPtoUnixEpoch = 2208988800;
	unsigned long long int secondsSinceEpoch = ms / this->msPerSec;
	const long int leapSeconds[] = {
		2272060800,		// 1 Jan 1972
		2287785600,		// 1 Jul 1972
		2303683200,		// 1 Jan 1973
		2335219200,		// 1 Jan 1974
		2366755200,		// 1 Jan 1975
		2398291200,		// 1 Jan 1976
		2429913600,		// 1 Jan 1977
		2461449600,		// 1 Jan 1978
		2492985600,		// 1 Jan 1979
		2524521600,		// 1 Jan 1980
		2571782400,		// 1 Jul 1981
		2603318400,		// 1 Jul 1982
		2634854400,		// 1 Jul 1983
		2698012800,		// 1 Jul 1985
		2776982400,		// 1 Jan 1988
		2840140800,		// 1 Jan 1990
		2871676800,		// 1 Jan 1991
		2918937600,		// 1 Jul 1992
		2950473600,		// 1 Jul 1993
		2982009600,		// 1 Jul 1994
		3029443200,		// 1 Jan 1996
		3076704000,		// 1 Jul 1997
		3124137600,		// 1 Jan 1999
		3345062400,		// 1 Jan 2006
		3439756800,		// 1 Jan 2009
		3550089600,		// 1 Jul 2012
		3644697600,		// 1 Jul 2015
		3692217600		// 1 Jan 2017
	};
	int leapSecondListSize = (sizeof(leapSeconds) / sizeof(*leapSeconds));
	int leapSecondCount = 0;
	for (int i = 0; i < leapSecondListSize; i++)
	{
		if (secondsSinceEpoch > leapSeconds[i] - NTPtoUnixEpoch)
			leapSecondCount++;
	}

	return leapSecondCount;
}
