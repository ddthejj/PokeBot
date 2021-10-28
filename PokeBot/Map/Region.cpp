#include "Region.h"

#include "Area.h"

#include <iostream>
#include <fstream>

Region::Region(int In_Gen)
{
	Gen = In_Gen;

	switch (Gen)
	{
	case 1:
	{
		std::string regionFilePath = std::string("../../../Content/Servers/Kanto.txt");
	}
	break;
	default:
	{
		
	}
	}
}

void Region::ParseFile(std::string regionFilePath)
{
	std::fstream file(regionFilePath);
	std::string line;

	while (getline(file, line))
	{
		Areas.push_back(new Area(line));
	}
}
