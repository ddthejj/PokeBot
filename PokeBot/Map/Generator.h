#pragma once

#include <map>
#include <vector>

enum class Type;
class Pokemon_Data;

class Generator
{
	std::map<Type, std::map<int, std::vector<Pokemon_Data*>>> SortedPokemon;

public:

	void SortPokemon(std::map<int, std::vector<Pokemon_Data*>> &pokedex);

	Pokemon_Data* RandomPokemon(Type type, int stage);
};