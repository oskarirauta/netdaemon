#pragma once

#include <string>
#include <vector>
#include "clock_time.hpp"

namespace settings {

	extern std::string wan_ifd;
	extern bool auto_renew;
	extern bool speed_testing;

	extern int minimum_required_ping_count;
	extern int maximum_ping_attempts;
	extern int ping_timeout;

	extern int failed_pings_threshold;
	extern int speed_test_interval;

	extern std::vector<std::string> ping_hosts;
	extern std::vector<timespan> speedtest_exclude_times;

}
