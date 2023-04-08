#include "states.hpp"

bool states::wan_enabled = false;
bool states::wan_online = false;
int states::ping_host_index = 0;
int states::state_delay = 1000;
bool states::should_override_speedtest = false;

states::state_enum states::current = STATE_IDLE;
