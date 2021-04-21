#ifndef MemoryManager_h
#define MemoryManager_h
#include "Kernel.h"

class MemoryManager
{
private:

	Kernel& _kernel;
	std::vector<std::string> data;

	void GetDataFromBUS(std::string);
	void PaginateMemory(std::string);

public:

	MemoryManager(Kernel&);
};

#endif
