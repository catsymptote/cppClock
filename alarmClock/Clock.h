#pragma once

#include <string>		// string for output

class Clock
{
public:
	Clock();
	Clock(unsigned int year, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second);
	~Clock();

private:
	unsigned int ms;
	bool displayClock;
	bool leapYear;

	unsigned int second;
	unsigned int minute;
	unsigned int hour;
	unsigned int day;
	unsigned int week;
	unsigned int month;
	int year;

private:
	bool updateNeeded();
	void updateClock();
	void clockLoop();
	void displayTime();
	std::string formatTime();
	void setTimeNow();
	bool isLeapYear();

public:
	unsigned int getTime();
	unsigned int getMonth();

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

