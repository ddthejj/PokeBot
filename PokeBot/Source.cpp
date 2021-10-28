#include "SleepyHandler/PokeBotClient.cpp"
#include <iostream>
#include <fstream>

int main() 
{
	std::ifstream file("../../../../token.txt", std::ios::in);
	char buffer[512];
	file.getline(buffer, 512);


	PokeBotClient client(buffer, SleepyDiscord::USER_CONTROLED_THREADS);
	client.run();
}