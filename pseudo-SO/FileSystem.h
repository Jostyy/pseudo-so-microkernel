#ifndef FileSystem_h
#define FileSystem_h
#include "Kernel.h"
#include <fstream>
#include <sstream>
#include <iterator>

class FileSystem
{
private:

	Kernel& _kernel;
	std::vector<std::string> disk;

	void ReadFile(std::string);
	void DataBUS();

public:

	FileSystem(Kernel&);
	std::vector<std::string> GetDataFromDisk(); 
};

#endif

