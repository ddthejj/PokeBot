#include "Encounter.h"
#include "Encounter.h"

#include "../Users/User.h"
#include "../Pokemon/PokemonInstance.h"

Encounter::Encounter()
{
	type = EventType::Encounter;
}

void Encounter::Begin()
{
	//Event::Begin();
}

void Encounter::End()
{
	Event::End();
}

void Encounter::Run(DiscordUser* trainer)
{
	End();
	delete encounteredMon;
}

void Encounter::Catch(DiscordUser* trainer)
{
	trainer->AddPokemon(encounteredMon);

	End();
}
