#pragma once

#include "PokemonDatabase.h"

class DiscordUser;

class Encounter
{
public:

	Pokemon_Data encounteredMon;

	void Begin();
	void End();
	void Catch(DiscordUser* trainer);
};