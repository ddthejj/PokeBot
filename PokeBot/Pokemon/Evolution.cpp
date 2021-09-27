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
		return new EvolutionMethodTime();
		break;
	}
	case 'f': // friendship
	{
		return new EvolutionMethodFriendship();
		break;
	}
	case 'u': // use item
	{
		return new EvolutionMethodUseableItem();
		break;
	}
	case 'o': // trade
	{
		return new EvolutionMethodTrade();
		break;
	}
	case 's': // stat
	{
		return new EvolutionMethodStat();
		break;
	}
	case 'h': // held item
	{
		return new EvolutionMethodHeldItem();
		break;
	}
	case 'm': // move
	{
		return new EvolutionMethodMove();
		break;
	}
	case 'p': // party
	{
		return new EvolutionMethodParty();
		break;
	}
	case'q': // personality
	{
		return new EvolutionMethodPersonality();
		break;
	}
	case 'g': // gender
	{
		return new EvolutionMethodGender();
		break;
	}
	case 'l': // form
	{
		return new EvolutionMethodForm();
		break;
	}
	case 'a': // area
	{
		return new EvolutionMethodArea();
		break;
	}
	case 'w': // trade with
	{
		return new EvolutionMethodTradeWith();
		break;
	}
	case '~': // upsidedown
	{
		return new EvolutionMethodUpsidedown();
		break;
	}
	case 'i': // affection
	{
		return new EvolutionMethodAmie();
		break;
	}
	case 'c': // weather
	{
		return new EvolutionMethodWeather();
		break;
	}
	case 'k': // candy
	{
		return new EvolutionMethodCandy();
		break;
	}
	case 'y': // nature
	{
		return new EvolutionMethodNature();
		break;
	}
	case 'd': // damage
	{
		return new EvolutionMethodDamage();
		break;
	}
	case 'z': // spin
	{
		return new EvolutionMethodSpin();
		break;
	}
	case 'j':
	{
		return new EvolutionMethodCrit();
		break;
	}
	}

	assert(false);
	return nullptr;
}

std::string EvolutionMethod::ToString()
{
	switch (Type)
	{
	case EvolutionType::Level:
	{
		return std::string("Level Up");
	}
	case EvolutionType::Time:
	{
		return std::string("Time of Day");
	}
	case EvolutionType::Friendship:
	{
		return std::string("Friendship");
	}
	case EvolutionType::UseableItem:
	{
		return std::string("Use Item");
	}
	case EvolutionType::HeldItem:
	{
		return std::string("Held Item");
	}
	case EvolutionType::Trade:
	{
		return std::string("Trade");
	}
	case EvolutionType::Stat:
	{
		return std::string("Stats");
	}
	case EvolutionType::Move:
	{
		return std::string("Learned Move");
	}
	case EvolutionType::Party:
	{
		return std::string("Party Condition");
	}
	case EvolutionType::Personality:
	{
		return std::string("At Random");
	}
	case EvolutionType::Gender:
	{
		return std::string("Gender");
	}
	case EvolutionType::Form:
	{
		return std::string("Form");
	}
	case EvolutionType::Area:
	{
		return std::string("At Location");
	}
	case EvolutionType::TradeWith:
	{
		return std::string("Trade With");
	}
	case EvolutionType::Upsidedown:
	{
		return std::string("Upsidedown");
	}
	case EvolutionType::Amie:
	{
		return std::string("Amie");
	}
	case EvolutionType::Weather:
	{
		return std::string("Weather");
	}
	case EvolutionType::Nature:
	{
		return std::string("Nature");
	}
	case EvolutionType::Candy:
	{
		return std::string("Candy");
	}
	case EvolutionType::Damage:
	{
		return std::string("Damage");
	}
	case EvolutionType::Spin:
	{
		return std::string("Spin");
	}
	case EvolutionType::Crit:
	{
		return std::string("Crit");
	}
	default:
	{
		assert(false);
		return std::string("");
	}
	}
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

bool EvolutionMethodForm::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodAmie::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodDamage::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodSpin::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}

bool EvolutionMethodCrit::CanEvolve(Pokemon_Instance* pokemon)
{
	return false;
}
