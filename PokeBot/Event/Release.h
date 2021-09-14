#pragma once

#include "Event.h"

class DiscordUser;

class ReleaseEvent : public Event
{
	bool IsConfirming = false;
	int index = 0;

public:

	ReleaseEvent() { type = EventType::Release; }

	virtual void Begin() override;
	virtual void End() override;

	void SelectMon(int In_Index);
	void Cancel();
	void Confirm(DiscordUser* user);

	int Index() { return index; }
};