#include "dogelog.h"
#include <string>
using namespace doge;
using namespace std;

int main(int args, char * argv[])
{
	DailyRotateLogger logger("test", 0, 0);

	bool is_true = true, is_false = false;
	int integer = 123456;
	int32_t i32 = -12345678;
	uint32_t u32 = 123456789;
	int64_t i64 = -1234567881233456789;
	uint64_t u64 = 1234567881233456789;
	double d = -1232443567890.123456789;
	string test_string("test_string");

	logger.Info().Write("%d", 1);
	logger.Info().Write("%d", 2).Write("%s%s", "aaaa", "wwww");
	logger.Info().Write("%d", 3);
	logger.Info()<<"is_true:"<<is_true<<" is_false:"<<is_false;
	logger.Info()<<"std::string: "<<test_string;
	logger.Info()<<"input integer:"<<integer;
	logger.Info()<<"input i32:"<<i32;
	logger.Info()<<"input u32:"<<u32;
	logger.Info()<<"input i64:"<<i64;
	logger.Info()<<"input u64:"<<u64;
	logger.Info()<<"input double:"<<d;
}
