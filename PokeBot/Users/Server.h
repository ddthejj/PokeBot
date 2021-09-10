#pragma once
#include <map>

class DiscordUser;

class DiscordServer
{
	DiscordServer() = default;
	DiscordServer(int64_t In_ID);


	int64_t id = -1;

	std::map<int, DiscordUser> users;
};