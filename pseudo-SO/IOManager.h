#ifndef IOManager_h
#define IOManager_h
#include "Kernel.h"
#include <fstream>
#include <sstream>

class IOManager
{
	Kernel& _kernel;
	std::vector<std::string> data;
public:

	IOManager(Kernel&);
	void GetData(std::string);
	void ScheduleDisk();
};

#endif

