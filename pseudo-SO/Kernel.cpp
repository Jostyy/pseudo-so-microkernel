#include "Kernel.h"
#include <iostream>

//Atribui um comando à uma referência de uma função
//Um comando pode ter mais de uma função atribuido ao mesmo
void Kernel::Load(std::string const& command, ScriptFunction handler) {
	system[command].push_back(handler);
}

//Executa sequencialmente as funções de acordo com o comando
//Passa os dados via string
void Kernel::Run(std::string command) {
	auto it = this->system.find(command);
	if (this->system.find(command) == this->system.end())
		std::cout << "The command: " + command + " was not previously loaded!" << std::endl;
	else {
		for (auto func : it->second)
			func("");
	}
}

void Kernel::Run(std::string command, std::string data) {
	auto it = this->system.find(command);
	if (this->system.find(command) == this->system.end())
		std::cout << "The command: " + command + " was not previously loaded!" << std::endl;
	else {
		for (auto func : it->second)
			func(data);
	}	
}

