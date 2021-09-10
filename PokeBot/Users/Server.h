#pragma once
#include <map>

class DiscordUser;

class DiscordServer
{
	int id;

	std::map<int, DiscordUser> users;
};