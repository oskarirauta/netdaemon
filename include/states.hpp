#pragma once

#include <string>
#include "enumops.hpp"

enum state_enum {
	STATE_IDLE,
	STATE_WAN_CHECK,
	STATE_PING_CHECK,
	STATE_SPEEDTEST,
	STATE_RENEW,
	MAX_VALUE
}; ENABLE_ENUM_OPS(state_enum);

namespace states {

	extern bool wan_enabled;
	extern bool wan_online;
	extern int ping_host_index;
	extern int state_delay;
	extern bool should_override_speedtest;

	extern state_enum current;
}
