#include "settings.hpp"

std::string settings::wan_ifd = "wan";
bool settings::auto_renew = true;
bool settings::speed_testing = true;

std::vector<std::string> settings::ping_hosts = { "8.8.8.8", "google.com" };
std::vector<timespan> settings::speedtest_exclude_times;
