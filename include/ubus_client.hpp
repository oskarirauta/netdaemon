#pragma once

#include <string>
#include "ubus.hpp"
#include "json11.hpp"

namespace ubus {

	bool call(std::string path, std::string method, std::string msg, json11::Json& json);
}
