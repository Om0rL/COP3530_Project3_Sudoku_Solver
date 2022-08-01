#pragma once
#include<chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

class configuration_set {
public:
	bool show_time = false;
	bool show_recursion_count = false;
	void start();
	void end();
	int get_time_difference();
	void reset();
	void count();
	unsigned long long int get_recursion_count();
private:
	Clock::time_point _start;
	Clock::time_point _end;
	unsigned long long int recursion_counter = 0;
};
