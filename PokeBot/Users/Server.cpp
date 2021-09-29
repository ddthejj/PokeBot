#include "Server.h"

#include "User.h"
#include "../Pokemon/PokemonDatabase.h"

#include <string>

#include <iostream>
#include <fstream>

#include <Windows.h>

DiscordServer::DiscordServer(int64_t In_ID, Pokedex* dex)
{
	id = In_ID;

	char buffer[512];
	_i64toa(id, buffer, 10);

	std::string serverFilePath = std::string("../../../Content/Servers/") + buffer;

	DWORD ftyp = GetFileAttributes(serverFilePath.c_str());

	if (ftyp == INVALID_FILE_ATTRIBUTES) // error
	{
		DWORD error = GetLastError();

		if (error == ERROR_FILE_NOT_FOUND) // error could be that directory does not exist
		{
			// new server
			CreateDirectory(serverFilePath.c_str(), LPSECURITY_ATTRIBUTES());
		}
		return;
	}

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) // directory exists
	{
		// existing server

		// get the first file in the directory
		WIN32_FIND_DATA data;
		HANDLE hFind = FindFirstFile((serverFilePath + "/*").c_str(), &data);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			// for each file in the directory
			do
			{
				if (data.cFileName == std::string(".") || data.cFileName == std::string("..")) // current directory or previous directly
					continue;


				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					// directory?
				}
				else
				{
					// user found
					std::string filename = data.cFileName;
					int64_t userID = _atoi64(filename.c_str());

					DiscordUser* user = new DiscordUser(userID, id);

					std::fstream file(serverFilePath + "/" + filename);

					std::vector<std::string> lines;
					std::string line;

					while (getline(file, line))
					{
						lines.push_back(line);
					}

					file.close();

					user->ParseFile(lines, dex);


					users.insert(std::pair<int64_t, DiscordUser*>(userID, user));
				}

			} while (FindNextFile(hFind, &data) != 0);
			FindClose(hFind);
		}
	}
	else // directory does not exist
	{
		// new server
		CreateDirectory(serverFilePath.c_str(), LPSECURITY_ATTRIBUTES());
	}
}

DiscordServer::~DiscordServer()
{
	for (int i = 0; i < users.size(); i++)
	{
		delete users[i];
	}
}

bool DiscordServer::IsUserRegistered(int64_t In_ID)
{
	return users.count(In_ID) != 0;
}

DiscordUser* DiscordServer::RegisterUser(int64_t In_ID)
{
	DiscordUser* newUser = new DiscordUser();
	users.insert(std::make_pair(In_ID, newUser));

	char buffer[256];
	_i64toa(id, buffer, 10);

	std::string serverFilePath = std::string("../../../Content/Servers/") + buffer + "/";
	
	_i64toa(In_ID, buffer, 10);

	serverFilePath += buffer;

	CreateFile(serverFilePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, LPSECURITY_ATTRIBUTES(), CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	return newUser;
}

DiscordUser* DiscordServer::GetUser(int64_t ID)
{
	return users[ID];
}