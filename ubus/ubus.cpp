#include <iostream>
#include <thread>
#include <algorithm>
#include <string>

#include "app.hpp"
#include "logger.hpp"
#include "ubus_netdaemon.hpp"
#include "ubus.hpp"

std::string ubus_socket = "";
std::string ubus_node = "network.daemon";
struct ubus_context *ctx;
#ifndef b
struct blob_buf b;
#endif

static const struct ubus_method netguard_methods[] = {
	{ .name = "info", .handler = ubus_func_info },
	{ .name = "features", .handler = ubus_func_features, .policy = netguard_features_policy, .n_policy = ARRAY_SIZE(netguard_features_policy) },
};

static struct ubus_object_type netguard_object_type = {
	.name = ubus_node.c_str(),
	.id = 0,
	.methods = netguard_methods,
	.n_methods = ARRAY_SIZE(netguard_methods),
};

static struct ubus_object netguard_object = {
	.name = ubus_node.c_str(),
	.type = &netguard_object_type,
	.methods = netguard_methods,
	.n_methods = ARRAY_SIZE(netguard_methods),
};

int ubus_create(void) {

	if ( int ret = ubus_add_object(ctx, &netguard_object); ret != 0 ) {
		logger::error << app::name << ": creating ubus object " << ubus_node << ": failed" << std::endl;
		logger::error << "error: " << ubus_strerror(ret) << std::endl;
		return ret;
	} else logger::debug << app::name << ": creating ubus object " << ubus_node << ": OK" << std::endl;

	return 0;
}
