#include "configuration_set.h"

void configuration_set::start() {
	_start = Clock::now();
}

void configuration_set::end() {
	_end = Clock::now();
}

int configuration_set::get_time_difference() {
	milliseconds ms = std::chrono::duration_cast<milliseconds>(_end - _start);
	return ms.count();
}

void configuration_set::reset() {
	recursion_counter = 0;
}

void configuration_set::count() {
	recursion_counter++;
}

unsigned long long int configuration_set::get_recursion_count() {
	return recursion_counter;
}
