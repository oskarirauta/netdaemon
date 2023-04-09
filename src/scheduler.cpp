#include <iostream>

#include "states.hpp"
#include "stages.hpp"
#include "scheduler.hpp"

ENABLE_ENUM_OPS(stage_enum);

void run_task(void) {

	using namespace EnumOps;

	switch (states::current) {
		case STATE_IDLE:
			std::cout << "idling" << std::endl;
			break;
		case STATE_IFD_CHECK:
			stage::ifd_check();
			break;
		case STATE_PING_CHECK:
			std::cout << "using ping to determine if we are online or not" << std::endl;
			stage::ping_check();
			break;
		case STATE_SPEEDTEST:
			std::cout << "perform speedtest if we are online and it's time to do it.." << std::endl;
			break;
		case STATE_IFD_DISCONNECT:
			std::cout << "disconnect (ifdown wan) if renew is necessary" << std::endl;
			break;
		case STATE_WAIT:
			std::cout << "wait for few seconds before renewing wan if necessary" << std::endl;
			break;
		case STATE_IFD_RENEW:
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
