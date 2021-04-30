#include "ProcessManager.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//Instancia a classe para o kernel passando a refer�ncia de suas fun��es
ProcessManager::ProcessManager(Kernel& kernel) : _kernel(kernel)
{
	_kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	_kernel.Load("schedule process", [this](std::string const&) { return this->ScheduleProcessFIFO(); });
};

//TODO: gerenciador de processos deve ser capaz de aplicar o algoritmo
//de escalonamento definido por meio de par�metro pelo usu�rio do SO
void ProcessManager::GetDataFromBUS(std::string str)
{
	data.push_back(str);
}

void ProcessManager::ScheduleProcessFIFO()
{
	int t_arr = 0, t_exec = 0, aux = 0, aux2 = 0, total_exec = 0, t_wait = 0;
	float turnaround = 0.0, avg_wait = 0.0;
	vector<int> arrival;
	vector<int> exec;

	for(int i = 0; i < data.size(); i+=2){
		t_arr = atoi(data.at(i).c_str());
		t_exec = atoi(data.at(i+1).c_str());
		arrival.push_back(t_arr);
		exec.push_back(t_exec);
	}

	for(int i = 0; i < data.size()/2; i++){
		t_wait = total_exec - arrival[i];
		aux = aux + t_wait + exec[i];			// total turnaround time
		aux2 = aux2 + t_wait;					// total wait time
		total_exec = total_exec + exec[i];
	}

	turnaround = (float)aux/(float)(data.size()/2); // average turnaround time
	avg_wait = (float)aux2/(float)(data.size()/2);	// average wait time
	cout << "FIFO " << turnaround << " " << "t_response" << " " << avg_wait << endl;
}