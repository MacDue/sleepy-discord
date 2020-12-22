#include "interaction.h"

namespace SleepyDiscord {

  namespace ApplicationCommand {
    InteractionDataOption::InteractionDataOption(const json::Value& json)
      : InteractionDataOption(json::fromJSON<InteractionDataOption>(json)) {}
    InteractionDataOption::InteractionDataOption(const nonstd::string_view& json)
      : InteractionDataOption(json::fromJSON<InteractionDataOption>(json)) {}

    InteractionData::InteractionData(const json::Value& json)
      : InteractionData(json::fromJSON<InteractionData>(json)) {}
    InteractionData::InteractionData(const nonstd::string_view& json)
      : InteractionData(json::fromJSON<InteractionData>(json)) {}
  }

  Interaction::Interaction(const json::Value& json)
    : Interaction(json::fromJSON<Interaction>(json)) {}
  Interaction::Interaction(const nonstd::string_view& json)
    : Interaction(json::fromJSON<Interaction>(json)) {}
}
