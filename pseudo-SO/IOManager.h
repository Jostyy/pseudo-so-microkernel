#ifndef IOManager_h
#define IOManager_h
#include "Kernel.h"
#include <fstream>
#include <sstream>
#include <iostream>

class IOManager
{
private:

	Kernel& _kernel;
	std::vector<std::string> rawData;
	std::vector<int> data;
	int cilinders;
	int startingPos;

	void GetDataFromBUS(std::string);
	void ScheduleDiskFCFS();
	void ScheduleDiskSSF();
	void ScheduleDiskSCAN();

public:

	IOManager(Kernel&);
};

#endif

