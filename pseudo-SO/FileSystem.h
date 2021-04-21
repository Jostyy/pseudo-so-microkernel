#ifndef FileSystem_h
#define FileSystem_h
#include "Kernel.h"
#include <fstream>
#include <sstream>

class FileSystem
{
	Kernel& _kernel;
	std::vector<std::string> disk;
public:

	FileSystem(Kernel&);
	void ReadFile(std::string);
	void DataBUS();
	//std::vector<std::string> GetDataFromDisk(); <- apenas para testes
};

#endif

