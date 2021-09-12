#pragma once

#include <vector>
#include <string>

class Pokemon_Data;
class Pokedex;
class Encounter;
class Server;

class DiscordUser
{
	friend class Encounter;

	int64_t id = -1;
	int64_t serverID = -1;
	std::vector<Pokemon_Data> party;

	Encounter* activeEncounter = nullptr;

public:

	DiscordUser() = default;
	DiscordUser(int64_t In_ID, int64_t In_ServerID) { id = In_ID; serverID = In_ServerID; }
	~DiscordUser();

	void ParseFile(std::vector<std::string> lines, Pokedex pokedex);
	std::vector<std::string> ParseLine(std::string line, char delim);

	void Save();

	bool IsInEncounter() { return activeEncounter != nullptr; }
	void StartEncounter(Pokemon_Data mon);
	Pokemon_Data* CatchEncounter();
	void EndEncounter();

	const std::vector<Pokemon_Data> Party() { return party; }

private:

	void AddPokemon(Pokemon_Data mon);
};