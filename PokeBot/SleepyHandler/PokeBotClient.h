#pragma once
#include "sleepy_discord/sleepy_discord.h"

#include <vector>

class Pokedex;
class Generator;
class DiscordServer;

class PokeBotClient : public SleepyDiscord::DiscordClient
{
	Pokedex* dex;
	Generator* generator;

	std::map<int64_t, DiscordServer> joinedServers;

public:

	PokeBotClient(const std::string token, const char numOfThreads = SleepyDiscord::DEFAULT_THREADS);
	~PokeBotClient();

	using SleepyDiscord::DiscordClient::DiscordClient;

	void onMessage(SleepyDiscord::Message message) override;

	void onServer(SleepyDiscord::Server server) override;

	void pkbHelp(SleepyDiscord::Message message);

	void pkbData(SleepyDiscord::Message message);

	void pkbGenerate(SleepyDiscord::Message message);

	void pkbEncounter(SleepyDiscord::Message message);

	void pkbCatch(SleepyDiscord::Message message);

	void pkbRun(SleepyDiscord::Message message);

	void pkbParty(SleepyDiscord::Message message);

	void pkbRelease(SleepyDiscord::Message message);

	void pkbCancel(SleepyDiscord::Message message);

	void pkbYes(SleepyDiscord::Message message);

	void pkbNo(SleepyDiscord::Message message);
};