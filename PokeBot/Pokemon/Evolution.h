#pragma once

#include <functional>
#include <vector>
#include <string>

class Pokemon_Data;
class Pokemon_Instance;
class Item;
class Move;
enum class Pokemon_Gender;
enum class Weather;


enum class EvolutionType
{
	None,
	Level,
	Time,
	Friendship,
	UseableItem,
	HeldItem,
	Trade,
	Stat,
	Move,
	Party,
	Personality,
	Gender,
	Area,
	TradeWith,
	Upsidedown,
	Weather,
	Nature,
	Candy
};

enum class TimeOfDay
{
	Dawn,
	Day,
	Dusk,
	Night
};

class EvolutionMethod
{
protected:

	EvolutionType Type;

public:

	EvolutionMethod() { Type = EvolutionType::None; };
	static EvolutionMethod* MakeEvolutionMethod(std::string method);

	virtual bool CanEvolve(Pokemon_Instance* pokemon) = 0;

	EvolutionType GetEvolutionType() { return Type; }
};

class EvolutionMethodLevel : public EvolutionMethod
{
	int Level = -1;

public:

	EvolutionMethodLevel() { Type = EvolutionType::Level; };
	EvolutionMethodLevel(int In_Level) : EvolutionMethodLevel() { Level = In_Level; }

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodTime : public EvolutionMethod
{
	TimeOfDay Time;

public:

	EvolutionMethodTime() { Type = EvolutionType::Time; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodFriendship : public EvolutionMethod
{
public:

	EvolutionMethodFriendship() { Type = EvolutionType::Friendship; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodUseableItem : public EvolutionMethod
{
	Item* UseableItem;

public:

	EvolutionMethodUseableItem() { Type = EvolutionType::UseableItem; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnItemUsed() {}
};

class EvolutionMethodHeldItem : public EvolutionMethod
{
	Item* HeldItem;

public:

	EvolutionMethodHeldItem() { Type = EvolutionType::HeldItem; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;
};

class EvolutionMethodTrade : public EvolutionMethod
{
public:

	EvolutionMethodTrade() { Type = EvolutionType::Trade; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnTrade() {}
};

class EvolutionMethodStat : public EvolutionMethod
{
	std::function<bool(Pokemon_Instance*)> Comparison;

public:

	EvolutionMethodStat() { Type = EvolutionType::Stat; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodMove : public EvolutionMethod
{
	Move* EvoMove;

public:

	EvolutionMethodMove() { Type = EvolutionType::Move; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodParty : public EvolutionMethod
{
	std::function<bool(std::vector<Pokemon_Instance*>)> Comparison;

public:

	EvolutionMethodParty() { Type = EvolutionType::Party; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodPersonality : public EvolutionMethod
{
	// idek 

public:

	EvolutionMethodPersonality() { Type = EvolutionType::Personality; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodGender : public EvolutionMethod
{
	Pokemon_Gender Gender;

public:

	EvolutionMethodGender() { Type = EvolutionType::Gender; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;
};

class EvolutionMethodArea : public EvolutionMethod
{
	// area variable?

public:

	EvolutionMethodArea() { Type = EvolutionType::Area; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodTradeWith : public EvolutionMethodTrade
{
	Pokemon_Data* FriendMon;

public:

	EvolutionMethodTradeWith() { Type = EvolutionType::TradeWith; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	void OnTrade() {}
};

class EvolutionMethodUpsidedown : public EvolutionMethod
{
public:

	EvolutionMethodUpsidedown() { Type = EvolutionType::Upsidedown; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;
};

class EvolutionMethodWeather : public EvolutionMethod
{
	Weather EvoWeather;

public:

	EvolutionMethodWeather() { Type = EvolutionType::Weather; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;
};

class EvolutionMethodNature : public EvolutionMethod
{
	std::function<bool(Pokemon_Data*)> Comparison;

public:

	EvolutionMethodNature() { Type = EvolutionType::Nature; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;
};

class EvolutionMethodCandy : public EvolutionMethod
{
public:

	EvolutionMethodCandy() { Type = EvolutionType::Candy; };

	virtual bool CanEvolve(Pokemon_Instance* pokemon) override;

	virtual bool OnCandy() {}
};
