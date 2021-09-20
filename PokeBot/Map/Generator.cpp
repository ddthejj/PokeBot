#include "Generator.h"
#include "../Pokemon/PokemonDatabase.h"

#include <time.h>
#include <random>

typedef std::mt19937 rng_type;
rng_type rng;

void Generator::SortPokemon(std::map<int, std::vector<Pokemon_Data*>> &pokedex)
{
	for (int type = 1; type != (int)Type::Type_Max; type++)
	{
		std::map<int, std::vector<Pokemon_Data>> typeMap;

		SortedPokemon.insert(std::make_pair((Type)type, std::map<int, std::vector<Pokemon_Data*>>())
		);

	}

	for (auto it = pokedex.begin(); it != pokedex.end(); ++it)
	{
		Pokemon_Data* pokemon = (it->second[0]);

		if (pokemon->Legedary)
			continue;

		if (pokemon->Type1 != Type::None)
		{
			if (!SortedPokemon[pokemon->Type1].count(pokemon->Stage))
			{
				SortedPokemon[pokemon->Type1].insert(std::pair<int, std::vector<Pokemon_Data*>>());
			}

			SortedPokemon[pokemon->Type1][pokemon->Stage].push_back(pokemon);
		}
		if (pokemon->Type2 != Type::None)
		{
			if (!SortedPokemon[pokemon->Type1].count(pokemon->Stage))
			{
				SortedPokemon[pokemon->Type1].insert(std::pair<int, std::vector<Pokemon_Data*>>());
			}

			SortedPokemon[pokemon->Type1][pokemon->Stage].push_back(pokemon);
		}
	}
}

Pokemon_Data* Generator::RandomPokemon(Type type, int stage)
{
	std::vector<Pokemon_Data*> pool = SortedPokemon[type][stage];
	
	rng_type::result_type const seedval = time(NULL);
	rng.seed(seedval);
	std::uniform_int_distribution<rng_type::result_type> udist(0, SortedPokemon[type][stage].size() - 1);
	rng_type::result_type random_number = udist(rng);

	return (SortedPokemon[type][stage][random_number]);
}