/*
Jônatas Rocha de Paiva - 140177043; Luiz Duarte - 140151958; Matheus Oliveira Braga; Pedro Egler
Programa feito baseado em um MicroKernel, conforme: https://4.bp.blogspot.com/-HlUFhj9VkbM/VQxj_z9HDeI/AAAAAAAAARc/2R28443FCGM/s1600/compara%C3%A7%C3%A3o%2Bde%2Bmodelos%2Bde%2Bkernels%2Bmonol%C3%ADtico%2Be%2Bmicro.png
*/

#include <iostream>
#include "Kernel.h"
#include "FileSystem.h"
#include "ProcessManager.h"
#include "MemoryManager.h"
#include "IOManager.h"
#include "CheckArgs.h"


int main(int argc, char* argv[])
{
	Kernel kernel;
	FileSystem fileSystem(kernel);
	ProcessManager processManager(kernel);
	MemoryManager memoryManager(kernel);
	IOManager ioManager(kernel);

	try
	{
		switch (CheckArgs::IsValid(argc, argv)) {
		case 1:
			/*
			kernel.Run("read", argv[2]);
			kernel.Run("bus");
			kernel.Run("schedule process");
			*/
			break;
		case 2:
			kernel.Run("read", argv[2]);
			kernel.Run("bus");
			kernel.Run("paginate memory");
			break;
		case 3:
			/*
			kernel.Run("read", argv[2]);
			kernel.Run("bus");
			kernel.Run("schedule disk");
			*/
			break;
		default: 
			std::cout << "Invalid option: must be from 1 to 3!" << std::endl;
			break;
		}
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
