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
	rng_type::result_type random_number = udist(rng);

	Data = data;
	PersonalityValue = random_number;
}

Pokemon_Gender Pokemon_Instance::GetGender()
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
