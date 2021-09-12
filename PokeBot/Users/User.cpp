#include "User.h"

#include "../Pokemon/Encounter.h"
#include "../Users/Server.h"

#include <Windows.h>

DiscordUser::~DiscordUser()
{
	if (activeEncounter)
	{
		delete activeEncounter;
		activeEncounter = nullptr;
	}
}

void DiscordUser::ParseFile(std::vector<std::string> lines, Pokedex dex)
{
	for (int i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> words = ParseLine(lines[i], ',');

		int pokemonID = atoi(words[0].c_str());

		party.push_back(dex.pokedex[pokemonID][0]);
	}
}

std::vector<std::string> DiscordUser::ParseLine(std::string line, char delim)
{
	std::vector<std::string> lineList;

	int charAt = 0;
	while (charAt < line.size())
	{
		char buffer[2048];
		int bufferAt = 0;

		while (charAt < line.size() && line[charAt] != delim)
		{
			buffer[bufferAt] = line[charAt];
			charAt++;
			bufferAt++;
		}

		buffer[bufferAt] = '\0';
		lineList.push_back(std::string(buffer));
		charAt++;
	}


	return lineList;
}

void DiscordUser::Save()
{
	char buffer[256];
	_i64toa(serverID, buffer, 10);

	std::string userFilePath = std::string("../../../Content/Servers/") + buffer + "/";

	_i64toa(id, buffer, 10);

	userFilePath += buffer;

	DeleteFile(userFilePath.c_str());
	HANDLE hfile = CreateFile(userFilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, LPSECURITY_ATTRIBUTES(), CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD bytesWritten = 0;

	for (int i = 0; i < party.size(); i++)
	{
		Pokemon_Data mon = party[i];
		char buffer [8];
		itoa(mon.DexNum, buffer, 10);
		std::string line = std::string(buffer) + '\n';

		WriteFile(hfile, line.c_str(), line.size(), &bytesWritten, NULL);
		bytesWritten += line.size();
	}

	CloseHandle(hfile);
}

void DiscordUser::StartEncounter(Pokemon_Data mon)
{
	if (activeEncounter)
	{
		return;
	}

	activeEncounter = new Encounter();
	activeEncounter->encounteredMon = mon;

	activeEncounter->Begin();
}

Pokemon_Data* DiscordUser::CatchEncounter()
{
	if (activeEncounter)
	{
		activeEncounter->Catch(this);
		delete activeEncounter;
		activeEncounter = nullptr;

		return &party[party.size() - 1];
	}

	return nullptr;
}

void DiscordUser::EndEncounter()
{
	if (activeEncounter)
	{
		activeEncounter->End();
		delete activeEncounter;
		activeEncounter = nullptr;
	}
}

void DiscordUser::AddPokemon(Pokemon_Data mon)
{
	party.push_back(mon);
	Save();
}
