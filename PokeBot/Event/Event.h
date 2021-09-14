#pragma once

enum class EventType
{
	None = -1,
	Encounter,
	Release,
	Event_Max
};

class Event
{
protected:

	bool isOver = false;
	EventType type = EventType::None;

public:

	virtual void Begin() = 0;
	virtual void End() { isOver = true; }
	
	bool IsOver() { return isOver; }
	bool IsType(EventType In_Type) { return type == In_Type; }
	EventType Type() { return type; }
};