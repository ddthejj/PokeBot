#include "Evolution.h"

#include "../Pokemon/PokemonDatabase.h"
#include "../Pokemon/PokemonInstance.h"

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
