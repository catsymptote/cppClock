#pragma once

#include <string>	// For std::string

class Clock
{
public:
	Clock();
	Clock(long long int year, unsigned int day, unsigned int hour,
		unsigned int minute, unsigned int second);
	~Clock();

private:
	const unsigned short int msPerSec		= 1000;
	const unsigned short int secPerHour		= 3600;
	const unsigned short int secPerDay		= 86400;
	const unsigned short int secPerMin		= 60;
	const unsigned short int minPerHour		= 60;
	const unsigned short int hourPerDay		= 24;
	const unsigned short int dayPerYear		= 365;
	
	unsigned long long int ms;
	bool firstGetms = true;
	bool displayClock;
	bool leapYear;
	int timeZone;
	unsigned int lastMsMod = 0;

	unsigned int second;
	unsigned int minute;
	unsigned int hour;
	unsigned int day;
	unsigned int week;
	unsigned int weekOfYear;
	unsigned int month;
	unsigned int dayOfMonth;
	long long int year;
	int leapSec;

private:
	bool updateNeeded();
	void updateClock(unsigned int sec);
	void incrementDay();
	void clockLoop();
	void displayTime();
	void setTimeNow();
	bool isLeapYear();
	int leapSecondAdder(unsigned long long int ms);

public:
	std::string getFormatTime();
	std::string getFormatTimeAsText1();
	std::string getFormatTimeAsText2();
	unsigned long long int getms();
	unsigned int getMonthSetDay();
	std::string getMonthName(unsigned int monthNum);
	unsigned int getWeekNumber();
	unsigned int getWeekdayNumber();
	std::string getWeekdayName(unsigned int weekday);
	std::string getDayExtension(unsigned int day);

};
