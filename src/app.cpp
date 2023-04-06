#include <iostream>

#include "app.hpp"

void app::version_title() {

	std::cout << app::name << " v" << app::version << ( app::git_commit.empty() ? "" : " git commit " + app::git_commit ) << std::endl;
	std::cout << "author: Oskari Rauta" << std::endl;
	std::cout << "MIT License\n" << std::endl;
}

void app::version_info() {

	app::version_title();
	exit(0);
}
