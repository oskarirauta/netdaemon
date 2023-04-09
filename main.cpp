#include <iostream>
#include <string>
#include <thread>

#include "app.hpp"
#include "settings.hpp"
#include "logger.hpp"
#include "mutex.hpp"
#include "loop.hpp"
#include "ubus.hpp"

#include "clock_time.hpp"
#include "json11.hpp"

int main(int argc, char **argv) {

/*
	json11::Json my_json = json11::Json::object {
		{ "key1", "value1" },
		{ "key2", false },
		{ "key3", json11::Json::array { 1, 2, 3 } },
	};
	std::string json_str = my_json.dump();
	std::cout << "dump: " << json_str << std::endl;

	if ( my_json["key1"].is_string())
		std::cout << "key1: " << my_json["key1"].string_value() << std::endl;
	if ( my_json["key5"].is_string())
		std::cout << "key5: " << my_json["key5"].string_value() << std::endl;

	return 0;
*/
	app::parse_cmdline(argc, argv);

	// TODO: default should be "wan"
	settings::wan_ifd = "lan";

	uloop_init();

	if ( ctx = ubus_connect(ubus_socket == "" ? NULL : ubus_socket.c_str()); !ctx ) {
		logger::error << app::name << ": failed to connect to ubus socket " << ubus_socket << std::endl;
		return -1;
	}

	ubus_add_uloop(ctx);

	if ( int ret = ubus_create(); ret != 0 ) {
		ubus_free(ctx);
		return ret;
	}

	logger::verbose << app::name << ": starting main loop" << std::endl;
	std::thread loop_thread(run_main_loop);

	logger::info << app::name << ": service started" << std::endl;
	logger::vverbose << app::name << ": starting ubus service" << std::endl;

	uloop_run();
	uloop_done();
	ubus_free(ctx);

	logger::vverbose << app::name << ": ubus service has stopped" << std::endl;
	logger::vverbose << app::name << ": exiting main loop" << std::endl;

	main_loop.set_sig_exit(true);

	while ( main_loop.running())
		std::this_thread::sleep_for(
			std::chrono::milliseconds(SIG_DELAY));

	logger::vverbose << app::name << ": main loop stopped" << std::endl;

	loop_thread.join();

	logger::vverbose << app::name << ": ended service" << std::endl;

	return 0;
}
