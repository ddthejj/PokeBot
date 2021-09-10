#include "SleepyHandler/PokeBotClient.cpp"

int main() 
{
	PokeBotClient client("ODgzNDA0MzQ0NjU2MDIzNTcy.YTJcaA.BLuhhe3MikI-JkCURdKdoihy8nc", SleepyDiscord::USER_CONTROLED_THREADS);
	client.run();
}