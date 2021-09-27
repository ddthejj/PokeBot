#include "Evolution.h"

#include "../Pokemon/PokemonDatabase.h"
#include "../Pokemon/PokemonInstance.h"

#include <cassert>

EvolutionMethod* EvolutionMethod::MakeEvolutionMethod(std::string method)
{
	if (method.size() == 0)
	{
		return nullptr;
	}

	std::string methodParam = std::string(&(method.c_str()[1]));

	switch (method.c_str()[0])
	{
	case 'n': // level 
	{
		int level = atoi(methodParam.c_str());
		return new EvolutionMethodLevel(level);
		break;
	}
	case 't': // time
	{

		break;
	}
	case 'f': // friendship
	{

		break;
	}
	case 'u': // use item
	{

		break;
	}
	case 'o': // trade
	{

		break;
	}
	case 's': // stat
	{

		break;
	}
	case 'h': // held item
	{

		break;
	}
	case 'm': // move
	{

		break;
	}
	case 'p': // party
	{

		break;
	}
	case'q': // personality
	{

		break;
	}
	case 'g': // gender
	{

		break;
	}
	case 'l': // form
	{

		break;
	}
	case 'a': // area
	{

		break;
	}
	case 'w': // trade with
	{

		break;
	}
	case '~': // upsidedown
	{

		break;
	}
	case 'i': // affection
	{

		break;
	}
	case 'c': // weather
	{

		break;
	}
	case 'k': // candy
	{

		break;
	}
	case 'y': // nature
	{

		break;
	}
	case 'd': // damage
	{

		break;
	}
	case 'z': // spin
	{

		break;
	}
	}

	assert(true);
	return nullptr;
}

bool EvolutionMethodLevel::CanEvolve(Pokemon_Instance* pokemon)
{
	if (pokemon->GetLevel() >= Level)
	{
		return true;
	}
	return false;
}

bool EvolutionMethodTime::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodFriendship::CanEvolve(Pokemon_Instance* pokemon)
{
	if (pokemon->GetFriendship() > 160)
	{
		return true;
	}
	return false;
}

bool EvolutionMethodUseableItem::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodHeldItem::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodTrade::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodStat::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodMove::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodParty::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodPersonality::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodGender::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodArea::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodTradeWith::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodUpsidedown::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodWeather::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodNature::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodCandy::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}
