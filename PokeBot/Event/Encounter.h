#pragma once
#include "Event.h"

#include "../Pokemon/PokemonDatabase.h"

class DiscordUser;

class Encounter : public Event
{
public:

	Encounter();

	Pokemon_Data encounteredMon;

	virtual void Begin() override;
	virtual void End() override;

	void Run(DiscordUser* trainer);
	void Catch(DiscordUser* trainer);
};