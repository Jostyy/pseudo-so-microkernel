#include "IOManager.h"

//Instancia a classe para o kernel passando a refer�ncia de suas fun��es
IOManager::IOManager(Kernel& kernel) : _kernel(kernel)
{
	 _kernel.Load("load", [this](std::string const& str) { return this->GetData(str); });
	//_kernel.Load("start", [this](std::string const& str) { return this->do_something(); });
};
//TODO: o gerenciador de entrada/sa�da deve ser respons�vel
//por administrar o algoritmo especificado para a busca em disco
void IOManager::GetData(std::string str)
{
	data.push_back(str);
}

void IOManager::ScheduleDisk()
{

}