#pragma once

#include <string>
#include "enumops.hpp"

enum stage_enum {
	STATE_IDLE,
	STATE_IFD_CHECK,
	STATE_PING_CHECK,
	STATE_SPEEDTEST,
	STATE_IFD_DISCONNECT,
	STATE_WAIT,
	STATE_IFD_RENEW,
	MAX_VALUE
};

namespace states {

	extern bool ifd_enabled;
	extern bool ifd_online;
	extern int ping_host_index;
	extern int state_delay;
	extern bool should_override_speedtest;
	extern int failed_ping_count;
	extern bool ifd_needs_renew;

	extern stage_enum current;
}
