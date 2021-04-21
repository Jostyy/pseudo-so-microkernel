#ifndef MemoryManager_h
#define MemoryManager_h
#include "Kernel.h"

class MemoryManager
{
	Kernel& _kernel;
	std::vector<std::string> data;
public:

	MemoryManager(Kernel&);
	void GetData(std::string);
	void PaginateMemory(std::string);
};

#endif
