#pragma once

#include "../Pokemon/PokemonDatabase.h"

#include <vector>
#include <string>

class Pokemon_Data;
class Pokedex;
class Event;
enum class EventType;
class Server;

class DiscordUser
{
	int64_t id = -1;
	int64_t serverID = -1;
	std::vector<Pokemon_Data> party;

	Event* currentEvent = nullptr;

public:

	DiscordUser() = default;
	DiscordUser(int64_t In_ID, int64_t In_ServerID) { id = In_ID; serverID = In_ServerID; }
	~DiscordUser();

	void ParseFile(std::vector<std::string> lines, Pokedex pokedex);
	std::vector<std::string> ParseLine(std::string line, char delim);

	void Save();

	bool TryCreateEvent(EventType type, std::string& out_error);

	bool IsInEncounter();
	void StartEncounter(Pokemon_Data mon);
	Pokemon_Data* CatchEncounter();
	void RunEncounter();
	void EndEncounter();

	bool IsReleasingPokemon();
	void StartRelease();
	void SelectRelease(int index);
	void CancelRelease();
	std::string ConfirmRelease();

	const std::vector<Pokemon_Data> Party() { return party; }

	void AddPokemon(Pokemon_Data mon);
	void ReleasePokemon(int index);

private:

};