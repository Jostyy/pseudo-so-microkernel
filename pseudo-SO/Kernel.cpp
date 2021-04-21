#include "Kernel.h"

//Atribui um comando à uma referência de uma função
//Um comando pode ter mais de uma função atribuido ao mesmo
void Kernel::Load(std::string const& command, ScriptFunction handler) {
	system[command].push_back(handler);
}

//Executa sequencialmente as funções de acordo com o comando
//Passa os dados via string
void Kernel::Run(std::string command, std::string data) {
	auto it = this->system.find(command);
	for (auto func : it->second) {
		func(data);
	}
}

void Kernel::Run(std::string command) {
	auto it = this->system.find(command);
	for (auto func : it->second) {
		func("");
	}
}