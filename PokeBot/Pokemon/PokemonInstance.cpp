#include "PokemonInstance.h"
#include "PokemonDatabase.h"

#include <time.h>
#include <random>

typedef std::mt19937 rng_type;
rng_type rng;


Pokemon_Instance::Pokemon_Instance(Pokemon_Data* data)
{
	rng_type::result_type const seedval = (unsigned int)time(NULL);
	rng.seed(seedval);
	std::uniform_int_distribution<rng_type::result_type> udist(0, 4294967295);
	PersonalityValue = udist(rng);

	Data = data;
	Gender = SetGender();
	Nature = SetNature();
	IsShiny = SetShiny();

	udist = std::uniform_int_distribution<rng_type::result_type>(0, 31);
	HPIV = udist(rng);
	AttackIV = udist(rng);
	DefenseIV = udist(rng);
	SpecialAttackIV = udist(rng);
	SpecialDefenseIV = udist(rng);
	SpeedIV = udist(rng);
}

Pokemon_Instance::Pokemon_Instance(Pokemon_Data* data, uint32_t In_PersonalityValue,
	uint8_t In_HPIV, uint8_t In_AttackIV, uint8_t In_DefenseIV, uint8_t In_SpecialAttackIV, uint8_t In_SpecialDefenseIV, uint8_t In_SpeedIV,
	uint8_t In_HPEV, uint8_t In_AttackEV, uint8_t In_DefenseEV, uint8_t In_SpecialAttackEV, uint8_t In_SpecialDefenseEV, uint8_t In_SpeedEV)
{
	Data = data;
	PersonalityValue = In_PersonalityValue;
	HPIV = In_HPIV; AttackIV = In_AttackIV; DefenseIV = In_DefenseIV; SpecialAttackIV = In_SpecialAttackIV; SpecialDefenseIV = In_SpecialDefenseIV; SpeedIV = In_SpeedIV;
	HPEV = In_HPEV; AttackEV = In_AttackEV; DefenseEV = In_DefenseEV; SpecialAttackEV = In_SpecialAttackEV; SpecialDefenseEV = In_SpecialDefenseEV; SpeedEV = In_SpeedEV;

	Gender = SetGender();
	Nature = SetNature();
	IsShiny = SetShiny();
}

std::string Pokemon_Instance::Save()
{
	char buffer[32];
	itoa(Data->DexNum, buffer, 10);
	std::string line = std::string(buffer) + ',';
	itoa(PersonalityValue, buffer, 10);
	line += std::string(buffer) + ',';

	itoa(HPIV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(AttackIV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(DefenseIV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(SpecialAttackIV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(SpecialDefenseIV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(SpeedIV, buffer, 10);
	line += std::string(buffer) + ',';

	itoa(HPEV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(AttackEV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(DefenseEV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(SpecialAttackEV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(SpecialDefenseEV, buffer, 10);
	line += std::string(buffer) + ',';
	itoa(SpeedEV, buffer, 10);
	line += std::string(buffer) + ',';

	return line;
}

std::string Pokemon_Instance::GetSummary()
{
	char buffer[32];
	std::string line = Data->Name + "\n\n";

	itoa(HPIV, buffer, 10);
	line += std::string("HP IV: ") + std::string(buffer) + '\n';
	itoa(AttackIV, buffer, 10);
	line += std::string("Attack IV: ") + std::string(buffer) + '\n';
	itoa(DefenseIV, buffer, 10);
	line += std::string("Defense IV: ") + std::string(buffer) + '\n';
	itoa(SpecialAttackIV, buffer, 10);
	line += std::string("Special Attack IV: ") + std::string(buffer) + '\n';
	itoa(SpecialDefenseIV, buffer, 10);
	line += std::string("Special Defense IV: ") + std::string(buffer) + '\n';
	itoa(SpeedIV, buffer, 10);
	line += std::string("Speed IV: ") + std::string(buffer) + "\n\n";

	itoa(HPEV, buffer, 10);
	line += std::string("HP EV: ") + std::string(buffer) + '\n';
	itoa(AttackEV, buffer, 10);
	line += std::string("Attack EV: ") + std::string(buffer) + '\n';
	itoa(DefenseEV, buffer, 10);
	line += std::string("Defense EV: ") + std::string(buffer) + '\n';
	itoa(SpecialAttackEV, buffer, 10);
	line += std::string("Special Attack EV: ") + std::string(buffer) + '\n';
	itoa(SpecialDefenseEV, buffer, 10);
	line += std::string("Special Defense EV: ") + std::string(buffer) + '\n';
	itoa(SpeedEV, buffer, 10);
	line += std::string("Speed EV: ") + std::string(buffer) + "\n\n";

	if (Gender == Pokemon_Gender::Genderless)
	{
		line += "Genderless\n";
	}
	else
	{
		line += std::string("Gender: ") + (Gender == Pokemon_Gender::Male ? "Male\n" : "Female\n");
	}

	line += "Nature: " + NatureToString(Nature) + '\n';
	line += std::string("Shiny: ") + (IsShiny ? "Yes\n" : "No\n");

	return line;
}

std::string Pokemon_Instance::NatureToString(Pokemon_Nature nature)
{
	switch (nature)
	{
	case Pokemon_Nature::Hardy:
	{
		return "Hardy";
	}
	case Pokemon_Nature::Lonely:
	{
		return "Lonely";
	}
	case Pokemon_Nature::Brave:
	{
		return "Brave";
	}
	case Pokemon_Nature::Adamant:
	{
		return "Adamant";
	}
	case Pokemon_Nature::Naughty:
	{
		return "Naughty";
	}
	case Pokemon_Nature::Bold:
	{
		return "Bold";
	}
	case Pokemon_Nature::Docile:
	{
		return "Docile";
	}
	case Pokemon_Nature::Relaxed:
	{
		return "Relaxed";
	}
	case Pokemon_Nature::Impish:
	{
		return "Impish";
	}
	case Pokemon_Nature::Lax:
	{
		return "Lax";
	}
	case Pokemon_Nature::Timid:
	{
		return "Timid";
	}
	case Pokemon_Nature::Hasty:
	{
		return "Hasty";
	}
	case Pokemon_Nature::Serious:
	{
		return "Serious";
	}
	case Pokemon_Nature::Jolly:
	{
		return "Jolly";
	}
	case Pokemon_Nature::Naive:
	{
		return "Naive";
	}
	case Pokemon_Nature::Modest:
	{
		return "Modest";
	}
	case Pokemon_Nature::Mild:
	{
		return "Mild";
	}
	case Pokemon_Nature::Quiet:
	{
		return "Quiet";
	}
	case Pokemon_Nature::Bashful:
	{
		return "Bashful";
	}
	case Pokemon_Nature::Rash:
	{
		return "Rash";
	}
	case Pokemon_Nature::Calm:
	{
		return "Calm";
	}
	case Pokemon_Nature::Gentle:
	{
		return "Gentle";
	}
	case Pokemon_Nature::Sassy:
	{
		return "Sassy";
	}
	case Pokemon_Nature::Careful:
	{
		return "Careful";
	}
	case Pokemon_Nature::Quirky:
	{
		return "Quirky";
	}
	}
}

Pokemon_Gender Pokemon_Instance::SetGender()
{
	if (Data->Genderless)
	{
		return Pokemon_Gender::Genderless;
	}
	else
	{
		unsigned int threshold = (Data->FemalePercentage * 256) - 1;

		if (PersonalityValue % 256 > threshold)
		{
			return Pokemon_Gender::Male;
		}
		else
		{
			return Pokemon_Gender::Female;
		}
	}
}

Pokemon_Nature Pokemon_Instance::SetNature()
{
	switch (PersonalityValue % 25)
	{
	case 0:
		return Pokemon_Nature::Hardy;
	case 1:
		return Pokemon_Nature::Lonely;
	case 2:
		return Pokemon_Nature::Brave;
	case 3:
		return Pokemon_Nature::Adamant;
	case 4:
		return Pokemon_Nature::Naughty;
	case 5:
		return Pokemon_Nature::Bold;
	case 6:
		return Pokemon_Nature::Docile;
	case 7:
		return Pokemon_Nature::Relaxed;
	case 8:
		return Pokemon_Nature::Impish;
	case 9:
		return Pokemon_Nature::Lax;
	case 10:
		return Pokemon_Nature::Timid;
	case 11:
		return Pokemon_Nature::Hasty;
	case 12:
		return Pokemon_Nature::Serious;
	case 13:
		return Pokemon_Nature::Jolly;
	case 14:
		return Pokemon_Nature::Naive;
	case 15:
		return Pokemon_Nature::Modest;
	case 16:
		return Pokemon_Nature::Mild;
	case 17:
		return Pokemon_Nature::Quiet;
	case 18:
		return Pokemon_Nature::Bashful;
	case 19:
		return Pokemon_Nature::Rash;
	case 20:
		return Pokemon_Nature::Calm;
	case 21:
		return Pokemon_Nature::Gentle;
	case 22:
		return Pokemon_Nature::Sassy;
	case 23:
		return Pokemon_Nature::Careful;
	case 24:
		return Pokemon_Nature::Quirky;
	}
}

bool Pokemon_Instance::SetShiny()
{
	return (PersonalityValue / (65536)) < 16;
}

int8_t Pokemon_Instance::SetAbility()
{
	if (Data->Ability2 != -1)
	{
		return PersonalityValue & (1 << 16);
	}
	else
	{
		return 0;
	}
}
