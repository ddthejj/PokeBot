#pragma once

#include <vector>

class Area
{
	Area* North;
	Area* South;
	Area* East;
	Area* West;

	std::vector<Area*> Access;
}