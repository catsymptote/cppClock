// alarmClock.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <thread>

#include "Clock.h"


void clkStart()
{
	//Clock clk(2018, 366, 22, 00, 0);
	Clock clk;
	//unsigned int year, unsigned int day, unsigned int hour, unsigned int minute, unsigned int second

	while (false) {
		std::cout << "|";
	}
}

void testThread()
{
	while (true) {
		std::cout << "-";
	}
}

int main()
{
	

	/// Create and start clock thread.
	std::thread clockThread(clkStart);

	/// End (join) clock thread.
	clockThread.join();
    return 0;
}
