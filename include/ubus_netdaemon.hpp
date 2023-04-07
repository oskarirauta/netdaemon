#pragma once

#include "ubus.hpp"

enum {
	NETGUARD_FEATURES_ARG1,
	__NETGUARD_FEATURES_ARGS_MAX
};

const struct blobmsg_policy netguard_features_policy[] = {
	[NETGUARD_FEATURES_ARG1] = { .name = "arg1", .type = BLOBMSG_TYPE_STRING },
};

int ubus_func_info(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg);

int ubus_func_features(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg);

/*
// template
int ubus_func_x(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg);
*/
