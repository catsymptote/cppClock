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

private:
	bool updateNeeded();
	void updateClock(unsigned int sec);
	void incrementDay();
	void clockLoop();
	void displayTime();
	void setTimeNow();
	bool isLeapYear();

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
