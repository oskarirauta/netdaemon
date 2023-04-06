#pragma once

#include <string>

#ifndef GIT_COMMIT
#define GIT_COMMIT ""
#endif

namespace app {

	static const std::string name = "netguard";
	static const std::string version = "0.8.0";
	static const std::string git_commit(GIT_COMMIT);

	void version_title();
	void version_info();
}
