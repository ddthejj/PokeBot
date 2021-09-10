#include "PokeBotClient.h"
#include <time.h>
#include <random>
#include <string.h>

typedef std::mt19937 rng_type;
rng_type rng;

void PokeBotClient::onMessage(SleepyDiscord::Message message)
{
	if (message.startsWith("-pkb "))
	{
		if (message.content == ("-pkb generate"))
		{
			pkbGenerate(message);
		}
		if (message.startsWith("-pkb data"))
		{
			pkbData(message);
		}
		if (message.startsWith("-pkb encounter"))
		{

		}
	}
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
			if (0 == stricmp(dex.pokedex[i].Name.c_str(), params))
			{
				auto monData = dex.pokedex[i];

				char num[32];
				itoa(i, num, 10);
				char hp[32];
				itoa(monData.Base_HP, hp, 10);
				char att[32];
				itoa(monData.Base_Attack, att, 10);
				char def[32];
				itoa(monData.Base_Defense, def, 10);
				char spa[32];
				itoa(monData.Base_SpAttack, spa, 10);
				char spd[32];
				itoa(monData.Base_SpDefense, spd, 10);
				char sp[32];
				itoa(monData.Base_Speed, sp, 10);
				char stage[32];
				itoa(monData.Stage, stage, 10);

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
		rng_type::result_type const seedval = time(NULL);
		rng.seed(seedval);
		std::uniform_int_distribution<rng_type::result_type> udist(1, dex.pokedex.size() + 1);
		rng_type::result_type random_number = udist(rng);

		Pokemon_Data monData = dex.pokedex[random_number];

		char num[32];
		itoa(random_number, num, 10);
		char hp[32];
		itoa(monData.Base_HP, hp, 10);
		char att[32];
		itoa(monData.Base_Attack, att, 10);
		char def[32];
		itoa(monData.Base_Defense, def, 10);
		char spa[32];
		itoa(monData.Base_SpAttack, spa, 10);
		char spd[32];
		itoa(monData.Base_SpDefense, spd, 10);
		char sp[32];
		itoa(monData.Base_Speed, sp, 10);

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
	rng_type::result_type const seedval = time(NULL);
	rng.seed(seedval);
	std::uniform_int_distribution<rng_type::result_type> udist(1, dex.pokedex.size() + 1);
	rng_type::result_type random_number = udist(rng);

	Pokemon_Data monData = dex.pokedex[random_number];

	sendMessage(message.channelID, std::string("Random Pokemon: ") + monData.Name);
}

void PokeBotClient::pkbEncounter(SleepyDiscord::Message message)
{

}
