#ifndef IOManager_h
#define IOManager_h
#include "Kernel.h"
#include <fstream>
#include <sstream>

class IOManager
{
private:

	Kernel& _kernel;
	std::vector<std::string> data;

	void GetDataFromBUS(std::string);
	void ScheduleDisk();

public:

	IOManager(Kernel&);
};

#endif

