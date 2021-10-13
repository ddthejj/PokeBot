#pragma once

#include <string>
#include <vector>

class Area;

class Region
{
	std::string Name;
	int Gen;
	std::vector<Area*> Areas;

	Region(int In_Gen);
};