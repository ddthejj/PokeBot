#include "Release.h"

#include "../Users/User.h"

void ReleaseEvent::Begin()
{
}

void ReleaseEvent::End() 
{
	Event::End();
}

void ReleaseEvent::SelectMon(int In_Index)
{
	index = In_Index;
	isConfirming = true;
}

void ReleaseEvent::Cancel()
{
	End();
}

void ReleaseEvent::Confirm(DiscordUser* user)
{
	user->ReleasePokemon(index);
	End();
}
