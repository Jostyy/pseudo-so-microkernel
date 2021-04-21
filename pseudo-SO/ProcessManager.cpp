#include "ProcessManager.h"

//Instancia a classe para o kernel passando a referência de suas funções
ProcessManager::ProcessManager(Kernel& kernel) : _kernel(kernel)
{
	_kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	_kernel.Load("start", [this](std::string const&) { return this->ScheduleProcess(); });
};

//TODO: gerenciador de processos deve ser capaz de aplicar o algoritmo
//de escalonamento definido por meio de parâmetro pelo usuário do SO
void ProcessManager::GetDataFromBUS(std::string str)
{
	data.push_back(str);
}

void ProcessManager::ScheduleProcess()
{

}