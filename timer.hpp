#ifndef _TIMER_  
#define _TIMER_ 

#include <iostream>
#include <string.h> // for memset
#include <stdio.h> // for printf
#include <cstdlib> // for rand()
#include <map> // to store timer stamp

#include <sys/time.h> 
#include <unistd.h>
#include <ctime>

using namespace std;
// timer class from light-forward
#define TIMER_BEGIN(event) Timer::Instance().start(event)
#define TIMER_END(event)   Timer::Instance().end(event)

class Timer {

private:
	Timer(){}
	
	map<string, timeval> start_times;

public:

	static Timer& Instance() {
		static Timer instance;
		return instance;
	}

	void start(string eventname) {
		timeval start_time;
		gettimeofday(&start_time,NULL);
		start_times[eventname] = start_time;
	}

	void end(string eventname) {

		timeval end_time;
		gettimeofday(&end_time,NULL);
		timeval start_time = start_times[eventname];
		double diff = 1000000.0*(end_time.tv_sec-start_time.tv_sec) + (end_time.tv_usec-start_time.tv_usec);
		diff/=1000.0;

		char out[256];
		sprintf(out, "Time consumption for event <%s> is: %f", eventname.c_str(), diff);
		// string outstr(out);
		// LOG(out);

		printf("<DEBUG> %s\n", out);
	}
};

#endif