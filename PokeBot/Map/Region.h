#pragma once

#include <string>
#include <vector>

class Area;

class Region
{
public:

	std::string Name;
	int Gen;
	std::vector<Area*> Areas;

	Region(int In_Gen);

private:

	void ParseFile(std::string regionFilePath);
};