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

	std::uniform_int_distribution<rng_type::result_type> udist(0, 31);
	HPIV = udist(rng);
	AttackIV = udist(rng);
	DefenseIV = udist(rng);
	SpecialAttackIV = udist(rng);
	SpecialDefenseIV = udist(rng);
	SpeedIV = udist(rng);
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
	return (PersonalityValue % (65536)) > 16;
}
