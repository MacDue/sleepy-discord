#pragma once

#include <string>
#include <optional>

#include "discord_object_interface.h"
#include "server.h"
#include "channel.h"
#include "snowflake.h"

namespace SleepyDiscord {

  namespace ApplicationCommand {

    struct InteractionDataOption {
      InteractionDataOption() = default;
		  InteractionDataOption(const json::Value & json);
		  InteractionDataOption(const nonstd::string_view & rawJSON);

      std::string name;
      std::string value = "";
      std::vector<InteractionDataOption> options;

      JSONStructStart
        std::make_tuple(
          json::pair(&InteractionDataOption::name   , "name"   , json::REQUIRIED_FIELD),
          json::pair(&InteractionDataOption::value  , "value"  , json::OPTIONAL_FIELD),
          json::pair<json::ContainerTypeHelper>(
                     &InteractionDataOption::options, "options", json::OPTIONAL_FIELD)
        );
      JSONStructEnd
    };

    struct InteractionData: IdentifiableDiscordObject<InteractionData> {
      InteractionData() = default;
      InteractionData(const json::Value & json);
      InteractionData(const nonstd::string_view & rawJSON);

      std::string name;
      std::vector<InteractionDataOption> options;

      JSONStructStart
        std::make_tuple(
          json::pair(&InteractionData::ID    , "id"     , json::REQUIRIED_FIELD),
          json::pair(&InteractionData::name  , "name"   , json::REQUIRIED_FIELD),
          json::pair<json::ContainerTypeHelper>(
                     &InteractionData::options, "options", json::OPTIONAL_FIELD)
        );
      JSONStructEnd
    };

  }

	struct Interaction : public IdentifiableDiscordObject<Interaction> {
	public:
		Interaction() = default;
		Interaction(const json::Value & json);
		Interaction(const nonstd::string_view & rawJSON);

    enum ResponseType {
      PONG = 1,
      ACKNOWLEDGE = 2,
      CHANNEL_MESSAGE	= 3,
      CHANNEL_MESSAGE_WITH_SOURCE =	4,
      ACK_WITH_SOURCE	= 5
    };

    enum InteractionType {
      PING = 1,
      APPLICATION_COMMAND = 2
    } type;

    std::optional<ApplicationCommand::InteractionData> commandData;
    Snowflake<Server> serverID;
    Snowflake<Channel> channelID;

    ServerMember author;
    std::string token;

    int version;

		JSONStructStart
			std::make_tuple(
				json::pair(&Interaction::ID         , "id"        , json::REQUIRIED_FIELD),
				json::pair<json::EnumTypeHelper>(
                   &Interaction::type       , "type"      , json::REQUIRIED_FIELD ),
				json::pair(&Interaction::commandData, "data"      , json::OPTIONAL_FIELD),
        json::pair(&Interaction::serverID   , "guild_id"  , json::REQUIRIED_FIELD),
        json::pair(&Interaction::channelID  , "channel_id", json::REQUIRIED_FIELD),
        json::pair(&Interaction::author     , "member"    , json::REQUIRIED_FIELD),
        json::pair(&Interaction::token      , "token"     , json::REQUIRIED_FIELD),
        json::pair(&Interaction::version    , "version"   , json::REQUIRIED_FIELD)
			);
		JSONStructEnd
	};
}
