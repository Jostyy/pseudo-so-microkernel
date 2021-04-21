#ifndef CheckArgs_h
#define CheckArgs_h
#include <stdexcept>
#include <limits>
#include <string>

class CheckArgs
{
public:

	static int IsValid(int argc, char** argv);
};
#endif

