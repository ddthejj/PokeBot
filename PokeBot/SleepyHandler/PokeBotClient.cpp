#include "PokeBotClient.h"

#include <time.h>
#include <random>
#include <string.h>

typedef std::mt19937 rng_type;
rng_type rng;

PokeBotClient::PokeBotClient(const std::string token, const char numOfThreads) : SleepyDiscord::DiscordClient(token, numOfThreads)
{
	generator.SortPokemon(dex.pokedex);
}

void PokeBotClient::onMessage(SleepyDiscord::Message message)
{
	if (message.startsWith("-pkb "))
	{
		DiscordUser* author;

		if (!joinedServers[message.serverID.number()].IsUserRegistered(message.author.ID.number())) // check if user is not registered
		{
			author = joinedServers[message.serverID.number()].RegisterUser(message.author.ID.number());
		}
		else
		{
			author = joinedServers[message.serverID.number()].GetUser(message.author.ID.number());
		}

		if (message.content == ("-pkb generate"))
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
	DiscordServer joinedServer = DiscordServer(serverID, dex);

	joinedServers.insert(std::pair<int64_t, DiscordServer>(serverID, joinedServer));
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

		for (int i = 1; i < dex.pokedex.size() + 1; i++)
		{
			if (0 == _stricmp(dex.pokedex[i][0].Name.c_str(), params))
			{
				auto monData = dex.pokedex[i][0];

				char num[32];
				_itoa_s(i, num, 10);
				char hp[32];
				_itoa_s(monData.Base_HP, hp, 10);
				char att[32];
				_itoa_s(monData.Base_Attack, att, 10);
				char def[32];
				_itoa_s(monData.Base_Defense, def, 10);
				char spa[32];
				_itoa_s(monData.Base_SpAttack, spa, 10);
				char spd[32];
				_itoa_s(monData.Base_SpDefense, spd, 10);
				char sp[32];
				_itoa_s(monData.Base_Speed, sp, 10);
				char stage[32];
				_itoa_s(monData.Stage, stage, 10);

				sendMessage(message.channelID,
					std::string("#") + num + " " + monData.Name
					+ "\n" + monData.TypeAsString()
					+ "\n\nHP: " + hp
					+ "\nAttack: " + att
					+ "\nDefense: " + def
					+ "\nSpecial Attack: " + spa
					+ "\nSpecial Defense: " + spd
					+ "\nSpeed: " + sp
					+ "\n\nLegendary: " + (monData.Legedary ? "yes" : "no")
					+ "\nStage: " + stage
				);

				return;
			}
		}

		sendMessage(message.channelID, std::string("Pokemon \"") + params + "\" not found.");

	}
	else
	{
		rng_type::result_type const seedval = (unsigned int)time(NULL);
		rng.seed(seedval);
		std::uniform_int_distribution<rng_type::result_type> udist(1, (int)dex.pokedex.size() + 1);
		rng_type::result_type random_number = udist(rng);

		Pokemon_Data monData = dex.pokedex[random_number][0];

		char num[32];
		_itoa_s(random_number, num, 10);
		char hp[32];
		_itoa_s(monData.Base_HP, hp, 10);
		char att[32];
		_itoa_s(monData.Base_Attack, att, 10);
		char def[32];
		_itoa_s(monData.Base_Defense, def, 10);
		char spa[32];
		_itoa_s(monData.Base_SpAttack, spa, 10);
		char spd[32];
		_itoa_s(monData.Base_SpDefense, spd, 10);
		char sp[32];
		_itoa_s(monData.Base_Speed, sp, 10);

		sendMessage(message.channelID,
			std::string("Random Pokemon Data: \n") +
			"#" + num + " " + monData.Name
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
	std::uniform_int_distribution<rng_type::result_type> udist(1, (int)dex.pokedex.size() + 1);
	rng_type::result_type random_number = udist(rng);

	Pokemon_Data monData = dex.pokedex[random_number][0];

	sendMessage(message.channelID, std::string("Random Pokemon: ") + monData.Name);
}

void PokeBotClient::pkbEncounter(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()].GetUser(message.author.ID.number());


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
				Pokemon_Data monData = generator.RandomPokemon(type, 1);
				sendMessage(message.channelID, std::string("Encountered random ") + params + " type Pokemon, " + monData.Name + "!");

				author->StartEncounter(monData);
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

			Pokemon_Data monData = generator.RandomPokemon((Type)random_number, 1);

			sendMessage(message.channelID,
				std::string("Encountered random Pokemon, " + monData.Name + "!")
			);

			author->StartEncounter(monData);
		}
		else
		{
			sendMessage(message.channelID, std::string("You're already in an encounter, ") + message.author.username);
		}
	}
}

void PokeBotClient::pkbCatch(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()].GetUser(message.author.ID.number());

	if (author->IsInEncounter())
	{
		Pokemon_Data* mon = author->CatchEncounter();
		sendMessage(message.channelID, std::string("You caught ") + mon->Name + "!");
	}
	else
	{
		sendMessage(message.channelID, std::string("What are you trying to catch, ") + message.author.username + "?");
	}
}

void PokeBotClient::pkbRun(SleepyDiscord::Message message)
{
	DiscordUser* author = joinedServers[message.serverID.number()].GetUser(message.author.ID.number());

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
	std::vector<Pokemon_Data> party = joinedServers[message.serverID.number()].GetUser(message.author.ID.number())->Party();
	std::string partyStr;

	for (int i = 0; i < party.size(); i++)
	{
		Pokemon_Data mon = party[i];

		partyStr += mon.Name;

		if (i < party.size() - 1)
		{
			partyStr += +",\n";
		}
	}

	sendMessage(message.channelID, std::string("Trainer ") + message.author.username + " has the Pokemon:\n" + partyStr);
}

void PokeBotClient::pkbRelease(SleepyDiscord::Message message)
{

}
