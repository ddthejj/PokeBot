#pragma once

#include "Event.h"

class DiscordUser;

class ReleaseEvent : public Event
{
	bool isConfirming = false;
	int index = 0;

public:

	ReleaseEvent() { type = EventType::Release; }

	virtual void Begin() override;
	virtual void End() override;

	void SelectMon(int In_Index);
	void Cancel();
	void Confirm(DiscordUser* user);
	bool IsConfirming() { return isConfirming; }

	int Index() { return index; }
};