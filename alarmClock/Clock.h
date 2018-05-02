#pragma once

#include <string>		// string for output

class Clock
{
public:
	Clock();
	Clock(long long int year, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second);
	~Clock();

private:
	unsigned long long int ms;
	bool displayClock;
	bool leapYear;

	unsigned int second;
	unsigned int minute;
	unsigned int hour;
	unsigned int day;
	unsigned int week;
	unsigned int month;
	unsigned int dayOfMonth;
	long long int year;

private:
	bool updateNeeded();
	void updateClock();
	void clockLoop();
	void displayTime();
	void setTimeNow();
	bool isLeapYear();

public:
	std::string getFormatTime();
	unsigned long long int getms();
	unsigned int getMonthSetDay();
	std::string getMonthName(unsigned int monthNum);

	unsigned int getSecond();
	unsigned int getMinute();
	unsigned int getHour();
	unsigned int getDay();
	unsigned int getYear();

	void setSecond(unsigned int second);
	void setMinute(unsigned int minute);
	void setHour(unsigned int hour);
	void setDay(unsigned int day);
	void setYear(unsigned int year);

};
