#include <iostream>

#include "states.hpp"
#include "scheduler.hpp"

ENABLE_ENUM_OPS(state_enum);

void run_task(void) {

	using namespace EnumOps;

	switch (states::current) {
		case STATE_IDLE:
			std::cout << "idling" << std::endl;
			break;
		case STATE_WAN_CHECK:
			std::cout << "checking if wan is enabled/brought up" << std::endl;
			break;
		case STATE_PING_CHECK:
			std::cout << "using ping to determine if we are online or not" << std::endl;
			break;
		case STATE_SPEEDTEST:
			std::cout << "perform speedtest if we are online and it's time to do it.." << std::endl;
			break;
		case STATE_DISCONNECT:
			std::cout << "disconnect (ifdown wan) if renew is necessary" << std::endl;
			break;
		case STATE_WAIT:
			std::cout << "wait for few seconds before renewing wan if necessary" << std::endl;
			break;
		case STATE_RENEW:
			std::cout << "renew if threshold has overflown for failed pings" << std::endl;
			break;
		case MAX_VALUE:
			std::cout << "this should never happen.." << std::endl;
			break;
		default:
			std::cout << "unknown state" << std::endl;
	}

	states::current++;

}
