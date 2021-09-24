#pragma once

class Pokemon_Data;
class Pokemon_Instance;


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


class EvolutionMethod
{
protected:

	EvolutionType type;

public:

	EvolutionMethod() { type = EvolutionType::None; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) = 0;

	EvolutionType GetEvolutionType() { return type; }
};

class EvolutionMethodLevel : public EvolutionMethod
{
	int Level = -1;

public:

	EvolutionMethodLevel() { type = EvolutionType::Level; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodTime : public EvolutionMethod
{
public:

	EvolutionMethodTime() { type = EvolutionType::Time; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodFriendship : public EvolutionMethod
{
public:

	EvolutionMethodFriendship() { type = EvolutionType::Friendship; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;

	void OnLevelUp() {}
};

class EvolutionMethodUseableItem : public EvolutionMethod
{
public:

	EvolutionMethodUseableItem() { type = EvolutionType::UseableItem; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodHeldItem : public EvolutionMethod
{
public:

	EvolutionMethodHeldItem() { type = EvolutionType::HeldItem; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodTrade : public EvolutionMethod
{
public:

	EvolutionMethodTrade() { type = EvolutionType::Trade; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodStat : public EvolutionMethod
{
public:

	EvolutionMethodStat() { type = EvolutionType::Stat; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodMove : public EvolutionMethod
{
public:

	EvolutionMethodMove() { type = EvolutionType::Move; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodParty : public EvolutionMethod
{
public:

	EvolutionMethodParty() { type = EvolutionType::Party; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodPersonality : public EvolutionMethod
{
public:

	EvolutionMethodPersonality() { type = EvolutionType::Personality; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodGender : public EvolutionMethod
{
public:

	EvolutionMethodGender() { type = EvolutionType::Gender; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodArea : public EvolutionMethod
{
public:

	EvolutionMethodArea() { type = EvolutionType::Area; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodTradeWith : public EvolutionMethodTrade
{
public:

	EvolutionMethodTradeWith() { type = EvolutionType::TradeWith; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodUpsidedown : public EvolutionMethod
{
public:

	EvolutionMethodUpsidedown() { type = EvolutionType::Upsidedown; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodWeather : public EvolutionMethod
{
public:

	EvolutionMethodWeather() { type = EvolutionType::Weather; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodNature : public EvolutionMethod
{
public:

	EvolutionMethodNature() { type = EvolutionType::Nature; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};

class EvolutionMethodCandy : public EvolutionMethod
{
public:

	EvolutionMethodCandy() { type = EvolutionType::Candy; };

	virtual bool CanEvolve(Pokemon_Data* pokemon) override;
};
