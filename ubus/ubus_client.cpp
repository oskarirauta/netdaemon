#include <string>

#include "app.hpp"
#include "logger.hpp"
#include "ubus_client.hpp"

bool ubus::call(std::string path, std::string method, std::string msg, json11::Json &json) {

	uint32_t id;
	static struct blob_buf _b;
	struct ubus_context *_ctx;
	int ret;

	if ( _ctx = ubus_connect(ubus_socket.empty() ? NULL : ubus_socket.c_str()); !_ctx ) {
		logger::error << app::name << ": ubus client connection " <<
			( ubus_socket.empty() ? "" : ( "to " + ubus_socket + " " )) << "failed" << std::endl;
		return false;
	}

	blob_buf_init(&_b, 0);

	if ( !msg.empty() && !blobmsg_add_json_from_string(&_b, msg.c_str())) {
		logger::error << app::name << ": ubus call failed for " << path << "::method json parse error for message " << msg << std::endl;
		ubus_free(_ctx);
		return false;
	}

	if ( ret = ubus_lookup_id(_ctx, path.c_str(), &id); ret ) {

		logger::error << app::name << ": ubus lookup failed for " << path << " with error " << ubus_strerror(ret) << std::endl;
		ubus_free(_ctx);
		return false;
	}

	ubus_request req{};

	if ( ret = ubus_invoke_async(_ctx, id, method.c_str(), _b.head, &req); ret ) {

		logger::error << app::name << ": ubus invoke failed for " << path << "::" << method << " with error " << ubus_strerror(ret) << std::endl;
		ubus_free(_ctx);
		return false;
	}

	req.data_cb = [](ubus_request* req, int, blob_attr* msg) {

		if ( req == nullptr || msg == nullptr )
			return;
		req -> priv = blob_memdup(msg);
	};

	if ( ret = ubus_complete_request(_ctx, &req, 0); ret ) {
		logger::error << app::name << ": ubus invoke failed for " << path << "::" << method << " with error " << ubus_strerror(ret) << std::endl;
		ubus_free(_ctx);
		return false;
	}

	std::string err;
	std::string res(blobmsg_format_json_indent((blob_attr*)req.priv, true, -1));
	if ( json = json11::Json::parse(res, err); !err.empty()) {
		logger::error << app::name << ": ubus invoke failed for " << path << "::" << method << ", result is not valid json" <<
		logger::detail(res) << std::endl;
		ubus_free(_ctx);
		return false;
	}

	ubus_free(_ctx);
	return true;
}
