#include "Server.h"

#include "User.h"

#include <iostream>
#include <fstream>

DiscordServer::DiscordServer(int64_t In_ID)
{
	id = In_ID;

	char buffer[512];
	itoa(id, buffer, 10);

	std::string serverFilePath = std::string("../../../Content/Servers/") + buffer;

	std::ifstream file(serverFilePath, std::ios::in);

	if (!file.is_open())
		return;



}