#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "../Pokemon/PokemonDatabase.h"
#include "../Map/Generator.h"
#include "../Users/Server.h"

#include <vector>


class PokeBotClient : public SleepyDiscord::DiscordClient
{
	Pokedex dex;
	Generator generator;

	std::map<int64_t, DiscordServer> joinedServers;

public:

	PokeBotClient(const std::string token, const char numOfThreads = SleepyDiscord::DEFAULT_THREADS);

	using SleepyDiscord::DiscordClient::DiscordClient;

	void onMessage(SleepyDiscord::Message message) override;

	void onServer(SleepyDiscord::Server server) override;

	void pkbData(SleepyDiscord::Message message);

	void pkbGenerate(SleepyDiscord::Message message);

	void pkbEncounter(SleepyDiscord::Message message);

	void pkbCatch(SleepyDiscord::Message message);

	void pkbParty(SleepyDiscord::Message message);
};