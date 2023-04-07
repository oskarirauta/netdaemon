#pragma once

#include <string>

namespace states {

	enum state_enum {
		STATE_BEGIN,
		STATE_WAIT,
		STATE_WAN_CHECK,
		STATE_RENEW,
		STATE_SPEEDTEST,
		STATE_LAST
	};

	extern bool wan_enabled = false;
	extern bool wan_online = false;
	extern int ping_host_index = 0;
	extern int state_delay = 1000;

	extern std::string wan_ifd;
	extern bool auto_renew;
	extern bool speed_testing;

}
