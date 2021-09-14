#pragma once
#include <map>

#include "User.h"

class DiscordServer
{

	int64_t id = -1;

	std::map<int64_t, DiscordUser> users;

public:
	DiscordServer() = default;
	DiscordServer(int64_t In_ID, Pokedex dex);

	bool IsUserRegistered(int64_t In_ID);
	DiscordUser* RegisterUser(int64_t In_ID);

	DiscordUser* GetUser(int64_t ID);
};