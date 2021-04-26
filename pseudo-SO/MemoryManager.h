#ifndef MemoryManager_h
#define MemoryManager_h
#include "Kernel.h"
#include <iostream>
#include <algorithm>

class MemoryManager
{
private:

	Kernel& _kernel;
	std::vector<std::string> data;

	void GetDataFromBUS(std::string);
	void PaginateMemoryFIFO();
	void PaginateMemorySC();
	void PaginateMemoryLRU();

public:

	MemoryManager(Kernel&);
};

#endif
