#include "PokeBotClient.h"

#include "../Pokemon/PokemonDatabase.h"
#include "../Pokemon/PokemonInstance.h"
#include "../Pokemon/Evolution.h"
#include "../Map/Generator.h"
#include "../Users/Server.h"
#include "../Event/Event.h"

#include <time.h>
#include <random>
#include <string.h>
#include <cstdio>

typedef std::mt19937 rng_type;
rng_type rng;

PokeBotClient::PokeBotClient(const std::string token, const char numOfThreads) : SleepyDiscord::DiscordClient(token, numOfThreads)
{
	dex = new Pokedex();
	generator = new Generator();

	generator->SortPokemon(dex->pokedex);
}

PokeBotClient::~PokeBotClient()
{
	delete dex;
	delete generator;

	for (int i = 0; i < joinedServers.size(); i++)
	{
		delete joinedServers[i];
	}
}

void PokeBotClient::onMessage(SleepyDiscord::Message message)
{
	if (message.startsWith("-pkb "))
	{
		DiscordUser* author;

		if (!joinedServers[message.serverID.number()]->IsUserRegistered(message.author.ID.number())) // check if user is not registered
		{
			author = joinedServers[message.serverID.number()]->RegisterUser(message.author.ID.number());
		}
		else
		{
			author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());
		}

		if (message.content == "-pkb help")
		{
			pkbHelp(message);
		}
		else if (message.content == ("-pkb generate"))
		{
			pkbGenerate(message);
		}
		else if (message.startsWith("-pkb data"))
		{
			pkbData(message);
		}
		else if (message.startsWith("-pkb encounter"))
		{
			pkbEncounter(message);
		}
		else if (message.startsWith("-pkb catch"))
		{
			pkbCatch(message);
		}
		else if (message.startsWith("-pkb run"))
		{
			pkbRun(message);
		}
		else if (message.startsWith("-pkb party"))
		{
			pkbParty(message);
		}
		else if (message.startsWith("-pkb release"))
		{
			pkbRelease(message);
		}
		else if (message.startsWith("-pkb cancel"))
		{
			pkbCancel(message);
		}
		else if (message.startsWith("-pkb yes"))
		{
			pkbYes(message);
		}
		else if (message.startsWith("-pkb no"))
		{
			pkbNo(message);
		}
		else if (message.startsWith("-pkb summary"))
		{
			pkbSummary(message);
		}
		else
		{
			const char* command;
			command = &message.content.c_str()[5];
			sendMessage(message.channelID, std::string("Unrecognized command \"") + command + "\"");
		}
	}
}

void PokeBotClient::onServer(SleepyDiscord::Server server)
{
	const int64_t serverID = server.ID.number();
	DiscordServer* joinedServer = new DiscordServer(serverID, dex);

	joinedServers.insert(std::pair<int64_t, DiscordServer*>(serverID, joinedServer));
}

void PokeBotClient::pkbHelp(SleepyDiscord::Message message)
{
	sendMessage(message.channelID,
		std::string("PokeBot commands:\
		\nData: -pkb data [pokemon name]\
		\nView the data of the selected Pokemon\
		\nEncounter: -pkb encounter [optional type]\
		\nEncounter a random pokemon, of the type if specified\
		\nCatch: -pkb catch\
		\nCatch the Pokemon you're in an encoutner with\
		\nRun: -pkb run\
		\nRun from the Pokemon you're in an encounter with\
		\nParty: -pkb party\
		\nView your party\
		\nRelease: -pkb release [optional number]\
		\nShows your party with numbers next to them if you don't specify a number\
		\nIf you do specify a number, prompts you to release that Pokemon\
		\nCancel: -pkb cancel\
		\nCancels the current action\
		\nYes: -pkb yes\
		\nAffirms the current action\
		\nNo: -pkb no\
		\nCancels the current action\
		"));
}

void PokeBotClient::pkbData(SleepyDiscord::Message message)
{
	if (message.length() > std::string("-pkb data").length())
	{
		const char* buffer = message.content.c_str();
		const char* params = &(buffer[std::string("pkb data").length() + 1]);

		// remove white space before parameters
		while (*params == ' ')
		{
			params++;
		}

		for (auto it = dex->pokedex.begin(); it != dex->pokedex.end(); ++it)
		{
			if (0 == _stricmp(dex->pokedex[it->first][0]->Name.c_str(), params))
			{
				Pokemon_Data* monData = dex->pokedex[it->first][0];

				char num[32];
				_itoa_s(it->first, num, 10);
				char hp[32];
				_itoa_s(monData->Base_HP, hp, 10);
				char att[32];
				_itoa_s(monData->Base_Attack, att, 10);
				char def[32];
				_itoa_s(monData->Base_Defense, def, 10);
				char spa[32];
				_itoa_s(monData->Base_SpAttack, spa, 10);
				char spd[32];
				_itoa_s(monData->Base_SpDefense, spd, 10);
				char sp[32];
				_itoa_s(monData->Base_Speed, sp, 10);
				char gen[32];
				_itoa_s(monData->Gen, gen, 10);
				char ht[32];
				sprintf_s(ht, "%.2f", monData->Height / 10.f);
				char wt[32];
				sprintf_s(wt, "%.2f", monData->Weight / 10.f);
				char fp[32];
				sprintf_s(fp, "%.2f", (float)(monData->FemalePercentage * (float)100.f));
				char mp[32];
				sprintf_s(mp, "%.2f", (float)((float)100.f - (monData->FemalePercentage * (float)100.f)));
				char xp[32];
				_itoa_s(monData->BaseXP, xp, 10);
				char cr[32];
				_itoa_s(monData->CaptureRate, cr, 10);
				char hap[32];
				_itoa_s(monData->BaseHappiness, hap, 10);
				char ec[32];
				_itoa_s(monData->EggCycles, ec, 10);

				char stage[32];
				_itoa_s(monData->Stage, stage, 10);
				std::string ability1;
				std::string ability2;
				std::string ability3;

				for (auto it = dex->abilityDex.begin(); it != dex->abilityDex.end(); it++)
				{
					if ((*it).second == monData->Ability1)
					{
						ability1 = (*it).first;
					}
					else if ((*it).second == monData->Ability2)
					{
						ability2 = (*it).first;
					}
					else if ((*it).second == monData->HiddenAbility)
					{
						ability3 = (*it).first;
					}
				}

				std::string dataString = std::string("#") + num + " " + monData->Name + ", The " + monData->Classification;

				if (monData->FormName != "")
				{
					dataString += std::string("\nForm: ") + monData->FormName + ' ' + monData->Name;
				}

				dataString += std::string("\n") + monData->TypeAsString() + " Type";

				if (monData->EvolvesFrom)
				{
					dataString += std::string("\nEvolves From: ") + monData->EvolvesFrom->Mon->Name;
				}
				if (monData->EvolvesTo.size())
				{
					dataString += std::string("\nEvolves Into: ");

					for (int i = 0; i < monData->EvolvesTo.size(); i++)
					{
						// cut out duplicate entries (megas, gmax, alolan / galarian forms, etc)
						if (i == 0 || monData->EvolvesTo[i]->Mon->Name != monData->EvolvesTo[0]->Mon->Name)
						{
							if (i != 0)
							{
								dataString += ", ";
							}

							dataString += monData->EvolvesTo[i]->Mon->Name;
							dataString += " - ";

							for (int j = 0; j < monData->EvolvesTo[i]->Method.size(); j++)
							{
								if (j != 0)
								{
									dataString += " and ";
								}

								dataString += monData->EvolvesTo[i]->MethodToString(j);
							}
						}
					}
				}


				if (monData->Ability1 != -1)
				{
					dataString += "\n\nAbility 1: " + ability1;
				}
				if (monData->Ability2 != -1)
				{
					dataString += "\nAbility 2: " + ability2;
				}
				if (monData->HiddenAbility != -1)
				{
					dataString += "\nHidden Ability: " + ability3;
				}

				dataString
					+= std::string("\n\nHP: ") + hp
					+ "\nAttack: " + att
					+ "\nDefense: " + def
					+ "\nSpecial Attack: " + spa
					+ "\nSpecial Defense: " + spd
					+ "\nSpeed: " + sp
					;

				if (!monData->Genderless)
				{
					dataString += std::string("\n\nMale: ") + mp + "%, Female: " + fp + "%";
				}
				else
				{
					dataString += "\n\nGenderless";
				}

				dataString +=
					std::string("\nGeneration: ") + gen
					+ "\n\Baby: " + (monData->IsBaby ? "yes" : "no")
					+ "\nLegendary: " + (monData->Legedary ? "yes" : "no")
					+ "\nMythical: " + (monData->Mythical ? "yes" : "no")
					+ "\n\nStage: " + stage
					+ "\nHeight: " + ht + 'm'
					+ "\nWeight: " + wt + "kg"
					+ "\n\nBase EXP: " + xp
					+ "\nCatch Rate: " + cr
					+ "\nEgg Group: " + monData->EggGroupAsString()
					+ "\nEgg Cycles: " + ec
					+ "\nBase Happiness: " + hap
					+ "\n\nColor: " + monData->ColorAsString()
					+ "\nShape: " + monData->ShapeAsString()
					;

				sendMessage(message.channelID, dataString);


				/*
				bool In_CanEvolve,
				*/


				return;
			}
		}

		sendMessage(message.channelID, std::string("Pokemon \"") + params + "\" not found.");

	}
	else
	{
		rng_type::result_type const seedval = (unsigned int)time(NULL);
		rng.seed(seedval);
		std::uniform_int_distribution<rng_type::result_type> udist(1, (int)dex->pokedex.size() + 1);
		rng_type::result_type random_number = udist(rng);

		Pokemon_Data* monData = dex->pokedex[random_number][0];

		char num[32];
		_itoa_s(random_number, num, 10);
		char hp[32];
		_itoa_s(monData->Base_HP, hp, 10);
		char att[32];
		_itoa_s(monData->Base_Attack, att, 10);
		char def[32];
		_itoa_s(monData->Base_Defense, def, 10);
		char spa[32];
		_itoa_s(monData->Base_SpAttack, spa, 10);
		char spd[32];
		_itoa_s(monData->Base_SpDefense, spd, 10);
		char sp[32];
		_itoa_s(monData->Base_Speed, sp, 10);

		sendMessage(message.channelID,
			std::string("Random Pokemon Data: \n") +
			"#" + num + " " + monData->Name
			+ "\nHP: " + hp
			+ "\nAttack: " + att
			+ "\nDefense: " + def
			+ "\nSpecial Attack: " + spa
			+ "\nSpecial Defense: " + spd
			+ "\nSpeed: " + sp
		);

	}
}

void PokeBotClient::pkbGenerate(SleepyDiscord::Message message)
{
	rng_type::result_type const seedval = (unsigned int)time(NULL);
	rng.seed(seedval);
	std::uniform_int_distribution<rng_type::result_type> udist(1, (int)dex->pokedex.size() + 1);
	rng_type::result_type random_number = udist(rng);

	Pokemon_Data* monData = dex->pokedex[random_number][0];

	sendMessage(message.channelID, std::string("Random Pokemon: ") + monData->Name);
}

void PokeBotClient::pkbEncounter(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());

	std::string error;
	if (!author->TryCreateEvent(EventType::Encounter, error))
	{
		sendMessage(message.channelID, std::string("You are currently ") + error + ", " + message.author.username);
		return;
	}

	if (message.length() > std::string("-pkb encounter").length())
	{
		const char* buffer = message.content.c_str();
		const char* params = &(buffer[std::string("pkb encounter").length() + 1]);

		// remove white space before parameters
		while (*params == ' ')
		{
			params++;
		}

		Type type = Pokemon_Data::StringToType(params);

		if (type != Type::None)
		{
			if (!author->IsInEncounter())
			{
				Pokemon_Data* monData = generator->RandomPokemon(type, 1);
				sendMessage(message.channelID, std::string("Encountered random ") + params + " type Pokemon, " + monData->Name + "!");

				//Pokemon_Instance* monInstance = new Pokemon_Instance(monData);
				//Pokemon_Gender gender = monInstance->Gender();

				author->StartEncounter(new Pokemon_Instance(monData));
			}
			else
			{
				sendMessage(message.channelID, std::string("You're already in an encounter, ") + message.author.username);
			}
		}
		else
		{
			sendMessage(message.channelID, std::string("Invalid Type ") + params);
		}

	}
	else
	{
		if (!author->IsInEncounter())
		{
			rng_type::result_type const seedval = (unsigned int)time(NULL);
			rng.seed(seedval);
			std::uniform_int_distribution<rng_type::result_type> udist(1, (int)Type::Type_Max - 1);
			rng_type::result_type random_number = udist(rng);

			Pokemon_Data* monData = generator->RandomPokemon((Type)random_number, 1);

			sendMessage(message.channelID,
				std::string("Encountered random Pokemon, " + monData->Name + "!")
			);

			author->StartEncounter(new Pokemon_Instance(monData));
		}
		else
		{
			sendMessage(message.channelID, std::string("You're already in an encounter, ") + message.author.username);
		}
	}
}

void PokeBotClient::pkbCatch(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());

	if (author->IsInEncounter())
	{
		Pokemon_Instance* mon = author->CatchEncounter();
		sendMessage(message.channelID, std::string("You caught ") + mon->GetSpecies()->Name + "!");
	}
	else
	{
		sendMessage(message.channelID, std::string("What are you trying to catch, ") + message.author.username + "?");
	}
}

void PokeBotClient::pkbRun(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());

	if (author->IsInEncounter())
	{
		author->RunEncounter();
		sendMessage(message.channelID, std::string("You escaped, ") + message.author.username + "!");
	}
	else
	{
		sendMessage(message.channelID, std::string("What are you trying to run from, ") + message.author.username + "?");
	}
}

void PokeBotClient::pkbParty(SleepyDiscord::Message message)
{
	std::vector<Pokemon_Instance*> party = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number())->Party();
	std::string partyStr;

	for (int i = 0; i < party.size(); i++)
	{
		Pokemon_Instance* mon = party[i];

		partyStr += mon->GetSpecies()->Name;

		if (i < party.size() - 1)
		{
			partyStr += +",\n";
		}
	}

	sendMessage(message.channelID, std::string("Trainer ") + message.author.username + " has the Pokemon:\n" + partyStr);
}

void PokeBotClient::pkbRelease(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());

	if (message.length() == std::string("-pkb release").length())
	{
		std::string error;
		if (!author->TryCreateEvent(EventType::Encounter, error))
		{
			sendMessage(message.channelID, std::string("You are currently ") + error + ", " + message.author.username);
			return;
		}

		if (!author->IsReleasingPokemon())
		{
			author->StartRelease();

			std::string partyStr;

			std::vector<Pokemon_Instance*> party = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number())->Party();
			for (int i = 0; i < party.size(); i++)
			{
				char buffer[8];
				_itoa_s(i + 1, buffer, 10);

				partyStr += buffer;
				partyStr += ": ";

				Pokemon_Instance* mon = party[i];

				partyStr += mon->GetSpecies()->Name;

				if (i < party.size() - 1)
				{
					partyStr += +"\n";
				}
			}


			sendMessage(message.channelID, std::string("Select a pokemon to release, ") + message.author.username + '\n' + partyStr);
		}
		else
		{
			sendMessage(message.channelID, std::string("You're already trying to release a Pokemon, ") + message.author.username);
		}
	}
	else
	{
		const char* buffer = message.content.c_str();
		const char* params = &(buffer[std::string("pkb release").length() + 1]);

		// remove white space before parameters
		while (*params == ' ')
		{
			params++;
		}
		std::string paramsStr(params);

		if (paramsStr == "cancel")
		{
			if (author->IsReleasingPokemon())
			{
				author->CancelRelease();
				sendMessage(message.channelID, std::string("Canceled release, ") + message.author.username);
			}
			else
			{
				sendMessage(message.channelID, std::string("What are you trying to cancel, ") + message.author.username + "?");
			}
		}
		else if (paramsStr == "yes")
		{
			if (author->IsReleasingPokemon())
			{
				if (author->IsConfirmingRelease())
				{
					std::string name = author->ConfirmRelease();
					sendMessage(message.channelID, std::string("Released Pokemon ") + name + " from your party, " + message.author.username);
				}
				else
				{
					sendMessage(message.channelID, std::string("Please select a Pokemon to release or cancel, ") + message.author.username);
				}
			}
			else
			{
				sendMessage(message.channelID, std::string("What are you trying to say yes to, ") + message.author.username + "?");
			}
		}
		else if (paramsStr == "no")
		{
			if (author->IsReleasingPokemon())
			{
				if (author->IsConfirmingRelease())
				{
					author->CancelRelease();
					sendMessage(message.channelID, std::string("Canceled release, ") + message.author.username);
				}
				else
				{
					sendMessage(message.channelID, std::string("Please select a Pokemon to release or cancel, ") + message.author.username);
				}
			}
			else
			{
				sendMessage(message.channelID, std::string("What are you trying to say no to, ") + message.author.username + "?");
			}
		}
		else
		{
			std::string::const_iterator it = paramsStr.begin();

			int releaseNum = atoi(params);

			if (releaseNum > 0 && releaseNum <= joinedServers[message.serverID.number()]->GetUser(message.author.ID.number())->Party().size())
			{
				author->SelectRelease(releaseNum - 1);
				sendMessage(message.channelID, std::string("Release pokemon \"") + author->Party()[releaseNum - 1]->GetSpecies()->Name + "\"?");
			}
			else
			{
				sendMessage(message.channelID, std::string("Unrecognized command \"") + params + "\"");
			}
		}
	}
}

void PokeBotClient::pkbCancel(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());

	if (author->IsInEvent())
	{
		switch (author->GetEventType())
		{
		case EventType::Encounter:
		{
			message.content = "-pkb run";
			pkbRun(message);
			return;
			break;
		}
		case EventType::Release:
		{
			message.content = "-pkb release cancel";
			pkbRelease(message);
			return;
			break;
		}
		default:
		{

			break;
		}
		}
	}

	sendMessage(message.channelID, std::string("What are you trying to cancel, ") + message.author.username + "?");
}

void PokeBotClient::pkbYes(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());

	if (author->IsInEvent())
	{
		switch (author->GetEventType())
		{
		case EventType::Encounter:
		{

			break;
		}
		case EventType::Release:
		{
			message.content = "-pkb release yes";
			pkbRelease(message);
			return;
			break;
		}
		default:
		{

			break;
		}
		}
	}

	sendMessage(message.channelID, std::string("What are you trying to say yes to, ") + message.author.username + "?");
}

void PokeBotClient::pkbNo(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());

	if (author->IsInEvent())
	{
		switch (author->GetEventType())
		{
		case EventType::Encounter:
		{

			break;
		}
		case EventType::Release:
		{
			message.content = "-pkb release no";
			pkbRelease(message);
			return;
			break;
		}
		default:
		{

			break;
		}
		}
	}

	sendMessage(message.channelID, std::string("What are you trying to say no to, ") + message.author.username + "?");
}

void PokeBotClient::pkbSummary(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number());

	if (message.length() == std::string("-pkb summary").length())
	{
		std::string partyStr;

		std::vector<Pokemon_Instance*> party = joinedServers[message.serverID.number()]->GetUser(message.author.ID.number())->Party();
		for (int i = 0; i < party.size(); i++)
		{
			char buffer[8];
			_itoa_s(i + 1, buffer, 10);

			partyStr += buffer;
			partyStr += ": ";

			Pokemon_Instance* mon = party[i];

			partyStr += mon->GetSpecies()->Name;

			if (i < party.size() - 1)
			{
				partyStr += +"\n";
			}
		}

		sendMessage(message.channelID, std::string("Select a pokemon to view the summary of, ") + message.author.username + '\n' + partyStr);

	}
	else
	{
		const char* buffer = message.content.c_str();
		const char* params = &(buffer[std::string("pkb release").length() + 1]);

		// remove white space before parameters
		while (*params == ' ')
		{
			params++;
		}
		std::string paramsStr(params);


		std::string::const_iterator it = paramsStr.begin();

		int summaryNum = atoi(params);

		if (summaryNum > 0 && summaryNum <= joinedServers[message.serverID.number()]->GetUser(message.author.ID.number())->Party().size())
		{
			std::string summary = author->Party()[summaryNum - 1]->GetSummary();
			sendMessage(message.channelID, summary);
		}
		else
		{
			sendMessage(message.channelID, std::string("Unrecognized command \"") + params + "\"");
		}
	}
}
