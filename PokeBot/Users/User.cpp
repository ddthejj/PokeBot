#include "User.h"

#include "../Event/Encounter.h"
#include "../Event/Release.h"
#include "../Users/Server.h"
#include "../Pokemon/PokemonDatabase.h"

#include <Windows.h>

DiscordUser::~DiscordUser()
{
	if (currentEvent)
	{
		delete currentEvent;
		currentEvent = nullptr;
	}
}

void DiscordUser::ParseFile(std::vector<std::string> lines, Pokedex* dex)
{
	for (int i = 0; i < lines.size(); i++)
	{
		std::vector<std::string> words = ParseLine(lines[i], ',');

		int pokemonID = atoi(words[0].c_str());

		party.push_back(dex->pokedex[pokemonID][0]);
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
		Pokemon_Data* mon = party[i];
		char buffer[8];
		itoa(mon->DexNum, buffer, 10);
		std::string line = std::string(buffer) + '\n';

		WriteFile(hfile, line.c_str(), line.size(), &bytesWritten, NULL);
		bytesWritten += line.size();
	}

	CloseHandle(hfile);
}

bool DiscordUser::TryCreateEvent(EventType type, std::string& out_error)
{
	if (!currentEvent) // user is not doing anything
	{
		switch (type)
		{
		case EventType::Encounter:
		{
			break;
		}
		case EventType::Release:
		{
			break;
		}
		default:
		{

		}
		}
		return true;
	}
	else  // user is in an event already
	{
		switch (currentEvent->Type())
		{
		case EventType::Encounter:
		{
			out_error = "in an encounter";
			break;
		}
		case EventType::Release:
		{
			out_error = "releasing a pokemon";
			break;
		}
		default:
		{

		}
		}
		return false;
	}
}

EventType DiscordUser::GetEventType()
{
	if (currentEvent)
	{
		return currentEvent->Type();
	}
	else
	{
		return EventType::None;
	}
}

bool DiscordUser::IsInEncounter()
{
	return (currentEvent && currentEvent->IsType(EventType::Encounter) && !currentEvent->IsOver());
}

void DiscordUser::StartEncounter(Pokemon_Data* mon)
{
	if (currentEvent)
	{
		return;
	}

	currentEvent = new Encounter();
	((Encounter*)currentEvent)->encounteredMon = mon;

	currentEvent->Begin();
}

Pokemon_Data* DiscordUser::CatchEncounter()
{
	if (currentEvent && currentEvent->IsType(EventType::Encounter))
	{
		((Encounter*)currentEvent)->Catch(this);
		delete currentEvent;
		currentEvent = nullptr;

		return party[party.size() - 1];
	}

	return nullptr;
}

void DiscordUser::RunEncounter()
{
	if (currentEvent && currentEvent->IsType(EventType::Encounter))
	{
		((Encounter*)currentEvent)->Run(this);
		delete currentEvent;
		currentEvent = nullptr;
	}
}

void DiscordUser::EndEncounter()
{
	if (currentEvent && currentEvent->IsType(EventType::Encounter))
	{
		currentEvent->End();
		delete currentEvent;
		currentEvent = nullptr;
	}
}

bool DiscordUser::IsReleasingPokemon()
{
	return (currentEvent && currentEvent->IsType(EventType::Release) && !currentEvent->IsOver());
}

void DiscordUser::StartRelease()
{
	if (currentEvent)
	{
		return;
	}

	currentEvent = new ReleaseEvent();

	currentEvent->Begin();
}

void DiscordUser::SelectRelease(int index)
{
	if (currentEvent && currentEvent->IsType(EventType::Release))
	{
		((ReleaseEvent*)currentEvent)->SelectMon(index);
	}
}

void DiscordUser::CancelRelease()
{
	if (currentEvent && currentEvent->IsType(EventType::Release))
	{
		((ReleaseEvent*)currentEvent)->Cancel();
		delete currentEvent;
		currentEvent = nullptr;
	}
}

std::string DiscordUser::ConfirmRelease()
{
	if (currentEvent && currentEvent->IsType(EventType::Release))
	{
		std::string releasedName = party[((ReleaseEvent*)currentEvent)->Index()]->Name;

		((ReleaseEvent*)currentEvent)->Confirm(this);
		delete currentEvent;
		currentEvent = nullptr;

		return releasedName;
	}

	return std::string();
}

bool DiscordUser::IsConfirmingRelease()
{
	if (currentEvent && currentEvent->IsType(EventType::Release))
	{
		return ((ReleaseEvent*)currentEvent)->IsConfirming();
	}
}

void DiscordUser::AddPokemon(Pokemon_Data* mon)
{
	party.push_back(mon);
	Save();
}

void DiscordUser::ReleasePokemon(int index)
{
	auto it = party.begin();

	for (int i = 0; i < index; i++)
	{
		it++;
	}

	party.erase(it);

	Save();
}
