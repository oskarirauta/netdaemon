#include "app.hpp"
#include "logger.hpp"
#include "mutex.hpp"
#include "ubus.hpp"

static void die_handler(int signum) {

	logger::debug << app::name << ": received TERM signal" << std::endl;

	if ( !uloop_cancelled) {
		logger::verbose << app::name << ": exiting ubus service" << std::endl;
		uloop_end();
	}
}

MutexStore mutex(die_handler);
