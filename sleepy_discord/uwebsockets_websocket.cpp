#include "uwebsockets_websocket.h"
#ifndef NONEXISTENT_UWEBSOCKETS
#include <iostream>

namespace SleepyDiscord {
	UWebSocketsDiscordClient::~UWebSocketsDiscordClient() {

	}

	UWebSocketsDiscordClient::UWebSocketsDiscordClient(const std::string token, const char numOfThreads) {

	}

	bool UWebSocketsDiscordClient::connect(const std::string & uri, GenericMessageReceiver* messageProcessor, WebsocketConnection* connection) {
    return true;
	}

	void UWebSocketsDiscordClient::run() {
	}

	Timer UWebSocketsDiscordClient::schedule(std::function<void()> code, const time_t milliseconds) {
    return {};
	}

	void UWebSocketsDiscordClient::runAsync() {
	}

	void UWebSocketsDiscordClient::disconnect(unsigned int code, const std::string reason, WebsocketConnection* connection) {

	}

	void UWebSocketsDiscordClient::send(std::string message, WebsocketConnection* connection) {
	}

#include "standard_config.h"


/* list of needed librarys to compile this
uWS.lib
libuv.lib
iphlpapi.lib
psapi.lib
userenv.lib
zlibstat.lib
*/


}
#endif
