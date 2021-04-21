#ifndef ProcessManager_h
#define ProcessManager_h
#include "Kernel.h"
#include <string>
#include <tuple>

class ProcessManager
{
	Kernel& _kernel;
	std::vector<std::string> data;
	//std::vector<std::tuple<int, int>> pair;

public:

	ProcessManager(Kernel&);
	void GetData(std::string);
	void ScheduleProcess();
};

#endif

