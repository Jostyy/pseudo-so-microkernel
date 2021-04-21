#ifndef ProcessManager_h
#define ProcessManager_h
#include "Kernel.h"
#include <string>
#include <tuple>

class ProcessManager
{
private:

	Kernel& _kernel;
	std::vector<std::string> data;
	//std::vector<std::tuple<int, int>> pair;

	void GetDataFromBUS(std::string);
	void ScheduleProcess();

public:

	ProcessManager(Kernel&);
};

#endif

