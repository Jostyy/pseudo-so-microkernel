/*
Jônatas Rocha de Paiva - 140177043; Luiz Duarte; Matheus Oliveira Braga; Pedro Egler
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

	/*
	*How to?
	kernel.Run("read",argv[2]);											<- usar kernel como intermediário
	std::vector<std::string> content = fileSystem.GetDataFromDisk();	<- apenas para testes
	for (auto it : content)
		std::cout << it << std::endl;
	*/

	try
	{
		switch (CheckArgs::IsValid(argc, argv)) {
		case 1:
			//ProcessManager processManager(kernel);
			//kernel.Run("", argv[2]);
			break;
		case 2:
			//MemoryManager memoryManager(kernel);
			//kernel.Run("", argv[2]);
			break;
		case 3:
			//IOManager ioManager(kernel);
			//kernel.Run("", argv[2]);
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
	/*
	std::string a = "10 20";
	std::string s = "split on    whitespace   ";
	std::vector<std::string> result;
	std::istringstream iss(a);
	for (std::string a; iss >> a; )
		result.push_back(a);
	std::cout << result[0] << std::endl;
    std::cout << "Hello World!\n"; 
	*/
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
