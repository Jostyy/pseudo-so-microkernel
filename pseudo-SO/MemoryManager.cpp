#include "MemoryManager.h"

//Instancia a classe para o kernel passando a referência de suas funções
MemoryManager::MemoryManager(Kernel& kernel) : _kernel(kernel)
{
	_kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	//_kernel.Load("start", [this](std::string const& str) { return this->do_something(); });
};
//TODO: O gerenciador de memória deve garantir que um processo não acesse as regiões de memória de um outro
//processo, e que o algoritmo de substituição de página seja adequadamente usado
void MemoryManager::GetDataFromBUS(std::string str)
{
	data.push_back(str);
}

void MemoryManager::PaginateMemory(std::string fname)
{

}