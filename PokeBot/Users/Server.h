#pragma once
#include <map>

#include "User.h"

class DiscordServer
{

	int64_t id = -1;

	std::map<int, DiscordUser> users;

public:
	DiscordServer() = default;
	DiscordServer(int64_t In_ID);

	bool IsUserRegistered(int64_t In_ID);
	void RegisterUser(int64_t In_ID);
};