#include "Server.h"

#include "User.h"

#include <string>

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <sys/stat.h>

DiscordServer::DiscordServer(int64_t In_ID)
{
	id = In_ID;

	char buffer[512];
	itoa(id, buffer, 10);

	std::string serverFilePath = std::string("../../../Content/Servers/") + buffer;

	struct stat info;
	if (stat(serverFilePath.c_str(), &info) != 0)
	{

	}
	else if (info.st_mode & S_IFDIR)
	{
		// existing server		
		std::vector<std::string> lines;
		std::string line;

		while (std::getline(f, line))
		{
			lines.push_back(line);
		}
	}
	else
	{
		// new server
		std::experimental::filesystem::create_directories(serverFilePath);
	}
}