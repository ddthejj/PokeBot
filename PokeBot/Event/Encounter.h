#pragma once
#include "Event.h"

class DiscordUser;
class Pokemon_Instance;

class Encounter : public Event
{
public:

	Encounter();

	Pokemon_Instance* encounteredMon = nullptr;

	virtual void Begin() override;
	virtual void End() override;

	void Run(DiscordUser* trainer);
	void Catch(DiscordUser* trainer);
};