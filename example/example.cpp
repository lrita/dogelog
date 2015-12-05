#include "dogelog.h"
#include <string>
using namespace doge;
using namespace std;

int main(int args, char * argv[])
{
	DailyRotateLogger logger("test", 0, 0);
#if 1
	logger.Info().Write("%d", 1);
	logger.Info().Write("%d", 2).Write("%s%s", "aaaa", "wwww");
	logger.Info().Write("%d", 3);
#endif
	string test("test");
	logger.Info()<<"111111"<<test;
}
