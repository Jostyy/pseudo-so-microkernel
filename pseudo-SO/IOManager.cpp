#include "IOManager.h"

//Instancia a classe para o kernel passando a referência de suas funções
IOManager::IOManager(Kernel& kernel) : _kernel(kernel)
{
	 _kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	_kernel.Load("schedule disk", [this](std::string const&) { return this->ScheduleDisk(); });
};
//TODO: o gerenciador de entrada/saída deve ser responsável
//por administrar o algoritmo especificado para a busca em disco
void IOManager::GetDataFromBUS(std::string str)
{
	data.push_back(str);
}

void IOManager::ScheduleDisk()
{

}