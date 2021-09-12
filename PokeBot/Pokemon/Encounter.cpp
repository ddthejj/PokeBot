#include "Encounter.h"

#include "../Users/User.h"

void Encounter::Begin()
{

}

void Encounter::End()
{

}

void Encounter::Catch(DiscordUser* trainer)
{
	trainer->AddPokemon(encounteredMon);

	End();
}
