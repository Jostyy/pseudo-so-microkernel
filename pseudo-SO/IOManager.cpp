#include "IOManager.h"

//Instancia a classe para o kernel passando a referência de suas funções
IOManager::IOManager(Kernel& kernel) : _kernel(kernel)
{
	 _kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	//_kernel.Load("start", [this](std::string const& str) { return this->do_something(); });
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