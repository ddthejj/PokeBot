#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "../Pokemon/PokemonDatabase.h"


class PokeBotClient : public SleepyDiscord::DiscordClient
{
	Pokedex dex;

public:

	using SleepyDiscord::DiscordClient::DiscordClient;

	void onMessage(SleepyDiscord::Message message) override;

	void pkbData(SleepyDiscord::Message message);

	void pkbGenerate(SleepyDiscord::Message message);

	void pkbEncounter(SleepyDiscord::Message message);
};