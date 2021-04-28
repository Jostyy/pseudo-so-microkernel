#include "MemoryManager.h"


//Instancia a classe para o kernel passando a refer�ncia de suas fun��es
MemoryManager::MemoryManager(Kernel& kernel) : _kernel(kernel)
{
	_kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	_kernel.Load("paginate memory", [this](std::string const& ) { return this->PaginateMemoryFIFO(); });
	_kernel.Load("paginate memory", [this](std::string const& ) { return this->PaginateMemorySC(); });
	_kernel.Load("paginate memory", [this](std::string const& ) { return this->PaginateMemoryLRU(); });
};
//TODO: O gerenciador de mem�ria deve garantir que um processo n�o acesse as regi�es de mem�ria de um outro
//processo, e que o algoritmo de substitui��o de p�gina seja adequadamente usado
void MemoryManager::GetDataFromBUS(std::string str)
{
	data.push_back(str);
	
}

void MemoryManager::PaginateMemoryFIFO()
{
	
	int fifo = 0, count = 0;
	int aux = std::atoi(data.at(0).c_str());

	std::vector<int> frame(aux, 0);

	for (int i = 1; i<data.size(); i++)
	{
		if (i == data.size()) break;
		else if ((std::find(frame.begin(), frame.end(), std::atoi(data.at(i).c_str()))) == frame.end()) {
			frame[fifo] = std::atoi(data.at(i).c_str());
			fifo = (fifo + 1) % aux;
			count++;
		}
	}
	std::cout << "FIFO " << count << std::endl;
}

void MemoryManager::PaginateMemorySC()
{

	int fifo = 0, count = 0;
	int aux = std::atoi(data.at(0).c_str());

	std::vector<int> frame(aux, 0);

	for (int i = 1; i < data.size(); i++)
	{
		if (i == data.size()) break;
		else if ((std::find(frame.begin(), frame.end(), std::atoi(data.at(i).c_str()))) == frame.end()) {
			frame[fifo] = std::atoi(data.at(i).c_str());
			fifo = (fifo + 1) % aux;
			count++;
		}
	}
	std::cout << "SC " << count << std::endl;
}

void MemoryManager::PaginateMemoryLRU()
{

	int fifo = 0, count = 0;
	int aux = std::atoi(data.at(0).c_str());

	std::vector<int> frame(aux, 0);

	for (int i = 1; i < data.size(); i++)
	{
		if (i == data.size()) break;
		else if ((std::find(frame.begin(), frame.end(), std::atoi(data.at(i).c_str()))) == frame.end()) {
			frame[fifo] = std::atoi(data.at(i).c_str());
			fifo = (fifo + 1) % aux;
			count++;
		}
	}
	std::cout << "LRU " << count << std::endl;
}