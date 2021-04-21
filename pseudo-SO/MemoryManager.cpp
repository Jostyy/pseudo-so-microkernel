#include "MemoryManager.h"

//Instancia a classe para o kernel passando a refer�ncia de suas fun��es
MemoryManager::MemoryManager(Kernel& kernel) : _kernel(kernel)
{
	_kernel.Load("load", [this](std::string const& str) { return this->GetData(str); });
	//_kernel.Load("start", [this](std::string const& str) { return this->do_something(); });
};
//TODO: O gerenciador de mem�ria deve garantir que um processo n�o acesse as regi�es de mem�ria de um outro
//processo, e que o algoritmo de substitui��o de p�gina seja adequadamente usado
void MemoryManager::GetData(std::string str)
{
	data.push_back(str);
}

void MemoryManager::PaginateMemory(std::string fname)
{

}