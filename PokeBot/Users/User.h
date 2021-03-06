#pragma once

#include <vector>
#include <string>

class Pokemon_Instance;
class Pokedex;
class Event;
enum class EventType;
class Server;

class DiscordUser
{
	int64_t id = -1;
	int64_t serverID = -1;
	std::vector<Pokemon_Instance*> party;

	Event* currentEvent = nullptr;

public:

	DiscordUser() = default;
	DiscordUser(int64_t In_ID, int64_t In_ServerID) { id = In_ID; serverID = In_ServerID; }
	~DiscordUser();

	void ParseFile(std::vector<std::string> lines, Pokedex* pokedex);
	std::vector<std::string> ParseLine(std::string line, char delim);

	void Save();

	bool TryCreateEvent(EventType type, std::string& out_error);
	bool IsInEvent() { return currentEvent; }
	EventType GetEventType();
	
	bool IsInEncounter();
	void StartEncounter(Pokemon_Instance* mon);
	Pokemon_Instance* CatchEncounter();
	void RunEncounter();
	void EndEncounter();

	bool IsReleasingPokemon();
	void StartRelease();
	void SelectRelease(int index);
	void CancelRelease();
	std::string ConfirmRelease();
	bool IsConfirmingRelease();

	const std::vector<Pokemon_Instance*> Party() { return party; }

	void AddPokemon(Pokemon_Instance* mon);
	void ReleasePokemon(int index);

private:

};