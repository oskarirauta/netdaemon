#pragma once

#include <string>
#include "enumops.hpp"

namespace states {

	enum state_enum {
		STATE_BEGIN,
		STATE_WAIT,
		STATE_WAN_CHECK,
		STATE_RENEW,
		STATE_SPEEDTEST,
		STATE_LAST
	}; ENABLE_ENUM_OPS(state_enum);

	extern bool wan_enabled;
	extern bool wan_online;
	extern int ping_host_index;
	extern int state_delay;
}
