#pragma once

#include "Event.h"

class ReleaseEvent : public Event
{
public:

	ReleaseEvent() { type = EventType::Release; }


};