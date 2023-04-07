#include <string>

#include "app.hpp"
#include "common.hpp"
#include "logger.hpp"
#include "mutex.hpp"
#include "ubus_netdaemon.hpp"

int ubus_func_info(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg) {

	logger::debug << app::name << ": ubus call " << ubus_node << "::info received" << std::endl;

	blob_buf_init(&b, 0);
	blobmsg_add_u8(&b, "running", true);
	ubus_send_reply(ctx, req, b.head);
	return 0;
}

int ubus_func_features(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg) {

	logger::debug << app::name << ": ubus call " << ubus_node << "::features received" << std::endl;

	struct blob_attr *tb[__NETGUARD_FEATURES_ARGS_MAX];
	blobmsg_parse(netguard_features_policy, ARRAY_SIZE(netguard_features_policy), tb, blob_data(msg), blob_len(msg));

	std::string arg1 = tb[NETGUARD_FEATURES_ARG1] ?
		std::string((char*)blobmsg_data(tb[NETGUARD_FEATURES_ARG1])) : "";

	if ( arg1.empty()) {
		logger::vverbose << app::name << ": ubus_" << ubus_node << "_features error, missing arg1" << std::endl;
		return UBUS_STATUS_INVALID_ARGUMENT;
	}

	blob_buf_init(&b, 0);

	blobmsg_add_string(&b, "arg1", arg1.c_str());
	ubus_send_reply(ctx, req, b.head);
	return 0;
}

/*
// template:

int ubus_func_x(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg) {

	logger::debug << app::name << ": ubus call " << ubus_node << "::func received" << std::endl;

	blob_buf_init(&b, 0);
	blobmsg_add_u8(&b, "bool", true);
	blobmsg_add_string(&b, "string", "string");
	ubus_send_reply(ctx, req, b.head);
	return 0;
}
*/
