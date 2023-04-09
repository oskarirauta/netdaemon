#include "app.hpp"
#include "json11.hpp"
#include "settings.hpp"
#include "ubus_client.hpp"
#include "logger.hpp"
#include "states.hpp"
#include "stages.hpp"

void stage::ifd_check(void) {

	logger::debug << app::name << ": checking if interface " << settings::wan_ifd << " is enabled" << std::endl;

	json11::Json json;
	bool ret = ubus::call("network.interface." + settings::wan_ifd, "status", "", json);

	if ( ret ) {
		bool new_value;
		if ( json["up"].is_bool())
			new_value = json["up"].bool_value();
		else ret = false;

		if ( ret && states::ifd_enabled != new_value ) {
			states::ifd_enabled = new_value;
			logger::info << app::name << ": interface " << settings::wan_ifd << " state is changed " << ( new_value ? "enabled" : "disabled" ) << std::endl;
		}
	}

	if ( !ret )
		logger::error << app::name << ": cannot check if interface " << settings::wan_ifd << " is enabled, ubus call has failed" << std::endl;

}
