#include <string>
#include "clock_time.hpp"

const std::string to_string(const clock_time& ct) {
	return ct.to_string();
}

const std::string to_string(const timespan& ts) {
	return ts.to_string();
}
