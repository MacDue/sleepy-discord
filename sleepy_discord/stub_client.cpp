#if _MSC_VER && !__INTEL_COMPILER
#pragma warning( disable: 4307 )  //ignore integer overflow, becuase we are taking advantage of it
#endif

#include <chrono>
#include <functional>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include "client.h"
#include "version_helper.h"
//#include "json.h"
#include "rapidjson/document.h"
#ifdef SLEEPY_USE_HARD_CODED_GATEWAY
	#include <cstring>
#endif

namespace SleepyDiscord {
	void BaseDiscordClient::start(const std::string _token, const char maxNumOfThreads, int _shardID, int _shardCount) {
		ready = false;
		quiting = false;
		bot = true;
		token = std::unique_ptr<std::string>(new std::string(_token)); //add client to list
		if (_shardID != 0 || _shardCount != 0)
			setShardID(_shardID, _shardCount);
	}

	BaseDiscordClient::~BaseDiscordClient() {
		ready = false;
	}

	void RateLimiter::limitBucket(Route::Bucket& bucket, time_t timestamp) {
		std::lock_guard<std::mutex> lock(mutex);
		buckets[bucket] = timestamp;
	}

	const time_t RateLimiter::getLiftTime(Route::Bucket& bucket, const time_t& currentTime) {
		return 0;
	}

	Response BaseDiscordClient::request(const RequestMethod method, Route path, const std::string jsonParameters,
		const std::vector<Part>& multipartParameters, RequestCallback callback, RequestMode mode
	) {
		//check if rate limited
		Response response;
		return response;
	}

	const Route BaseDiscordClient::path(const char * source, std::initializer_list<std::string> values) {
		return Route(source, values);
	}

	std::shared_ptr<ServerCache> BaseDiscordClient::createServerCache() {
		setServerCache(std::make_shared<ServerCache>());
		return getServerCache();
	}

	void BaseDiscordClient::setServerCache(std::shared_ptr<ServerCache> cache) {
		serverCache = cache;
		if ((ready || !isBot()) && serverCache->size() == 0)
			*serverCache = getServers().get<Cache>();
	}

	void BaseDiscordClient::onDepletedRequestSupply(const Route::Bucket&, time_t) {

	}

	void BaseDiscordClient::onExceededRateLimit(bool, std::time_t timeTilRetry, Request request) {

	}

	void BaseDiscordClient::updateStatus(std::string gameName, uint64_t idleSince, Status status, bool afk) {

	}

	void BaseDiscordClient::waitTilReady() {
		while (!ready) sleep(1000);
	}

	void BaseDiscordClient::setShardID(int _shardID, int _shardCount) {
		shardID = _shardID;
		shardCount = _shardCount;
	}

	void BaseDiscordClient::getTheGateway() {

	}

	void BaseDiscordClient::sendIdentity() {

	}

	void BaseDiscordClient::sendResume() {

	}

	void BaseDiscordClient::quit(bool isRestarting, bool isDisconnected) {

	}

	void BaseDiscordClient::restart() {

	}

	void BaseDiscordClient::reconnect(const unsigned int status) {

	}

	void BaseDiscordClient::disconnectWebsocket(unsigned int code, const std::string reason) {

	}

	bool BaseDiscordClient::sendL(std::string message) {
		return true;
	}

	constexpr unsigned int hash(const char* key, unsigned int i = 0) {
		return !key[i] ? 0 : (hash(key, i + 1) * 31) + key[i] - 'A';
	}

	void BaseDiscordClient::processMessage(const std::string &message) {

	}

	void BaseDiscordClient::processCloseCode(const int16_t code) {
		setError(code);

		switch (code) {
		//Just reconnect
		case 1006:
		case UNKNOWN_ERROR:
		case UNKNOWN_OPCODE:
		case DECODE_ERROR:
		case NOT_AUTHENTICATED:
		case ALREADY_AUTHENTICATED:
		case INVALID_SEQ:
		case RATE_LIMITED:
		case SESSION_TIMEOUT:
		default:
			break;

		case 1000:
			if (!isQuiting())
				break;
			//else fall through

		//Might be Unrecoveralbe
		//We may need to stop to prevent a restart loop.
		case AUTHENTICATION_FAILED:
		case INVALID_SHARD:
		case SHARDING_REQUIRED:
		case INVALID_INTENTS:
		case DISALLOWED_INTENTS:
			return quit(false, true);
			break;
		}
		reconnect(1001);
	}

	void BaseDiscordClient::heartbeat() {

	}

	void BaseDiscordClient::sendHeartbeat() {

	}

	const time_t BaseDiscordClient::getEpochTimeMillisecond() {
		auto ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
		return ms.time_since_epoch().count();
	}

	const std::string BaseDiscordClient::getEditPositionString(const std::vector<std::pair<std::string, uint64_t>>& positions) {
		std::vector<std::string> params(positions.size());
		for (auto& value : positions) {
			params.push_back(json::createJSON({
				{ "id", json::string(value.first) },
				{ "position", json::UInteger(value.second) }
			}));
		}
		return json::createJSONArray(params);
	}

	Route::Route(const std::string route, const std::initializer_list<std::string>& _values)
		: path(route), values(_values)
	{
		size_t targetSize = path.length();
		for (std::string replacement : values)
			targetSize += replacement.length();
		_url.reserve(targetSize);

		//In the future, use string view

		size_t offset = 0;
		for (std::string replacement : values) {
			const size_t start = path.find('{', offset);
			const size_t end = path.find('}', start);

			//the +1 and -1 removes the { and }
			const std::string identifier = path.substr(start + 1, end - start - 1);

			auto foundParam = majorParameters.find(identifier.c_str());
			if (foundParam != majorParameters.end()) {
				foundParam->second = replacement;
			}

			_url += path.substr(offset, start - offset);
			_url += replacement;
			offset = end + 1; //the +1 removes the }
		}
		_url += path.substr(offset, path.length() - offset);

	}

	Route::Route(const char* route) : Route(route, {}) {}

	const std::string Route::bucket(RequestMethod method) {
		std::string target;
		std::string methodString = std::to_string(method);
		size_t targetLength = methodString.length();
		for (auto param : majorParameters) {
			targetLength += param.second.length();
		}
		targetLength = path.length();
		target.reserve(targetLength);
		target += methodString;
		for (auto param : majorParameters) {
			target += param.second;
		}
		target += path;
		return target;
	}
}
