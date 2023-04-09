#include <iostream>

#include "logger.hpp"
#include "ubus.hpp"
#include "settings.hpp"
#include "app.hpp"

void app::version_info() {

	std::cout << app::name << " v" << app::version << ( app::git_commit.empty() ? "" : " git commit " + app::git_commit ) << std::endl;
}

void app::author_info() {

	std::cout << "author: Oskari Rauta" << std::endl;
	std::cout << "MIT License" << std::endl;
}

void app::usage(char* cmd) {
	std::cout << "\nusage: " << cmd << " [parameters]\n\n";
	std::cout << "   -h, --h                 show this help\n";
	std::cout << "   --version               show version\n";
	std::cout << "   -s, --socket path       connect to specified ubus socket\n";
	std::cout << "   -i, --interface ifd     monitor ifd interface as wan (default: wan)\n";
	std::cout << "   -q, --quiet             silence output\n";
	std::cout << "   --only-errors           output only errors\n";
	std::cout << "   -v, --verbose           verbose output\n";
	std::cout << "   -vv, --vverbose         more verbose output\n";
	std::cout << "   --debug                 maximum verbose output\n";
	std::cout << std::endl;
}

void app::parse_cmdline(int argc, char **argv) {

	std::vector<std::string> args(argv + 1, argv + argc);
	int log_level = 0;

	for (auto i = args.begin(); i != args.end(); i++) {

		if ( *i == "--help" || *i == "--h" || *i == "-h" || *i == "-?" || *i == "--usage" || *i == "-usage" ) {
			app::version_info();
			app::author_info();
			app::usage(argv[0]);
			exit(0);
		} else if (( *i == "-v" || *i == "--v" || *i == "--verbose" || *i == "-verbose" ) && log_level < 2 ) {
			if ( log_level < 0 ) {
				std::cout << "error: quiet and verbose logging cannot be used at same time." << std::endl;
				exit(-1);
			}
			log_level = 2;
		} else if (( *i == "-vv" || *i == "--vv" || *i == "--vverbose" || *i == "-vverbose" ) && log_level < 3 ) {
			if ( log_level < 0 ) {
				std::cout << "error: quiet and (extra) verbose logging cannot be used at same time." << std::endl;
				exit(-1);
			}
			log_level = 3;
		} else if (( *i == "-debug" || *i == "--debug" ) && log_level < 4 ) {
			if ( log_level < 0 ) {
				std::cout << "error: quiet and debug logging cannot be used at same time." << std::endl;
				exit(-1);
			}
			log_level = 4;
		} else if ( *i == "--only-errors" && log_level < 1 ) {
			if ( log_level < 0 ) {
				std::cout << "error: quiet and error-only logging cannot be used at same time." << std::endl;
				exit(-1);
			}
			log_level = 1;
		} else if ( *i == "-q" || *i == "--q" || *i == "-quiet" || *i == "--quiet" ) {
			if ( log_level > 0 ) {
				std::cout << "error: quiet and other logging levels cannot be used at same time." << std::endl;
				exit(-1);
			}
			log_level = -1;
		} else if ( *i == "-s" || *i == "--s" || *i == "--sock" || *i == "--socket" || *i == "-socket" ) {
			std::string this_arg = *i;
			if ( std::next(i) != args.end())
				ubus_socket = *++i;
			else {
				std::cout << "error: socket's path not given for " << this_arg << " option." << std::endl;
				exit(-1);
			}

			if ( ubus_socket.size() > 1 && ubus_socket.front() == '"' && ubus_socket.back() == '"' ) {
				ubus_socket.erase(0, 1);
				ubus_socket.erase(ubus_socket.size() - 1);
			}

			if ( ubus_socket.empty()) {
				std::cout << "error: socket's path not given for " << this_arg << " option." << std::endl;
				exit(-1);
			}
		} else if ( *i == "-i" || *i == "--i" || *i == "-interface" || *i == "--interface" || *i == "-ifd" || *i == "--ifd" ) {
			std::string this_arg = *i;
			if ( std::next(i) != args.end())
				settings::wan_ifd = std::string(*++i);
			else {
				std::cout << "error: interface name not given for " << this_arg << " option." << std::endl;
				exit(-1);
			}

			// TODO: check that ifd exists..

		} else if ( *i == "-version" || *i == "--version" ) {
			app::version_info();
			exit(0);
		} else if ( *i != "" ) {
			std::cout << "Unknown argument: " << *i << std::endl;
			app::usage(argv[0]);
			exit(-1);
		}
	}

	if ( log_level == -1 ) {
		logger::output_stream = nullptr;
		logger::error_stream = nullptr;
	} else if ( log_level == 1 )
		logger::output_stream = nullptr;
	else {
		logger::output_level[logger::verbose] = log_level > 1 ? true : false;
		logger::output_level[logger::vverbose] = log_level > 2 ? true : false;
		logger::output_level[logger::debug] = log_level > 3 ? true : false;
	}

	if ( log_level > 1 )
		app::version_info();
	if ( log_level > 2 )
		app::author_info();
}
