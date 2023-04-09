#include "json11.hpp"
#include "settings.hpp"
#include "ubus_client.hpp"
#include "states.hpp"
#include "stages.hpp"

void stage::wan_check(void) {

	json11::Json js;
	bool ret = ubus::call("network.interface." + settings::wan_ifd, "status", "", js);

//	if ( !ret || json

}
