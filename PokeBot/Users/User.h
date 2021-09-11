#pragma once

#include <vector>
#include <string>

class DiscordUser
{
	int64_t id;

public:

	DiscordUser() = default;
	DiscordUser(int64_t In_ID) { id = In_ID; }

	void ParseFile(std::vector<std::string> lines);
};