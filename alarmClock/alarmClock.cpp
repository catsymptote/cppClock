// alarmClock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <thread>

#include "Clock.h"


void clkStart()
{
	Clock clk;
	//Clock clk(2018, 366, 22, 00, 0);
	//Clock clk(long long int year, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second);
}

int main()
{
	/// Create and start clock thread.
	std::thread clockThread(clkStart);

	/// End (join) clock thread.
	clockThread.join();
    return 0;
}
