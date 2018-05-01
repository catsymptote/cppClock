#pragma once
class Clock
{
public:
	Clock();
	~Clock();

private:
	unsigned int ms;
	bool displayClock;

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

public:
	unsigned int getTime();

};

