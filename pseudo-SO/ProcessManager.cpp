#include "ProcessManager.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <fstream>
using namespace std;

//Instancia a classe para o kernel passando a refer�ncia de suas fun��es
ProcessManager::ProcessManager(Kernel& kernel) : _kernel(kernel)
{
	_kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	_kernel.Load("schedule process", [this](std::string const&) { return this->ScheduleProcessFIFO(); });
	_kernel.Load("schedule process", [this](std::string const&) { return this->ScheduleProcessSJF(); });
	_kernel.Load("schedule process", [this](std::string const&) { return this->ScheduleProcessRR(); });
};

//TODO: gerenciador de processos deve ser capaz de aplicar o algoritmo
//de escalonamento definido por meio de par�metro pelo usu�rio do SO
void ProcessManager::GetDataFromBUS(std::string str)
{
	data.push_back(str);
}

void ProcessManager::ScheduleProcessFIFO()
{
	int t_arr = 0, t_exec = 0, aux = 0, aux2 = 0;
	unsigned int total_exec = 0, t_wait = 0;
	float turnaround = 0.0, avg_wait = 0.0;
	fstream output;
	map<int, int> arrival;
	map<int, int> exec;

	output.open("FIFO.txt", fstream::in | fstream::out | fstream::trunc);

	for(int i = 0; i < data.size(); i+=2){
		t_arr = atoi(data.at(i).c_str());
		t_exec = atoi(data.at(i+1).c_str());
		arrival[i/2] = t_arr;
		exec[i/2] = t_exec;
	}

	map<int, int>::iterator min;
	while(!arrival.empty()){
		min = min_element(arrival.begin(), arrival.end(),		// extract the address of the minimum value from the map
			[](decltype(arrival)::value_type& l, decltype(arrival)::value_type& r) { return l.second < r.second; });
		if(min->second <= total_exec){		// check if minimum proccess has arrived 
			t_wait = total_exec - min->second;
			aux = aux + t_wait + exec[min->first];
			aux2 = aux2 + t_wait;
			output << "Rodar processo " << "[" << min->first << "]" << " de "
				<< "[" << total_exec << "]" << " ate " << "["
				<< total_exec + exec[min->first] << "]" << endl;
			total_exec = total_exec + exec[min->first];
			arrival.erase(min->first);
			exec.erase(min->first);
		}
		else
			total_exec++;
	}
	output.close();

	turnaround = (float)aux/(float)(data.size()/2); // average turnaround time
	avg_wait = (float)aux2/(float)(data.size()/2);	// average wait time
	cout << "FIFO " << turnaround << " " << avg_wait << " " << avg_wait << endl; // avg_wait = avg_response
}

void ProcessManager::ScheduleProcessSJF()
{
	int t_arr = 0, t_exec = 0, aux = 0, aux2 = 0, t_wait = 0;
	unsigned int total_exec = 0;
	float turnaround = 0.0, avg_wait = 0.0;
	fstream output;
	map<int, int> arrival;
	map<int, int> exec;

	output.open("SJF.txt", fstream::in | fstream::out | fstream::trunc);

	for(int i = 0; i < data.size(); i+=2){
		t_arr = atoi(data.at(i).c_str());
		t_exec = atoi(data.at(i+1).c_str());
		arrival[i/2] = t_arr;
		exec[i/2] = t_exec;
	}

	map<int, int>::iterator min;
	map<int, int>::iterator it;
	map<int, int> aux_map;
	while(!exec.empty()){
		for(it = arrival.begin(); it != arrival.end(); ++it){
			if(it->second <= total_exec){
				aux_map[it->first] = exec[it->first];
			}
		}
		if(!aux_map.empty()){
			min = min_element(aux_map.begin(), aux_map.end(),		// extract the address of the minimum value from the map
				[](decltype(arrival)::value_type& l, decltype(arrival)::value_type& r) { return l.second < r.second; });
			t_wait = total_exec - arrival[min->first];
			aux = aux + t_wait + min->second;
			aux2 = aux2 + t_wait;
			output << "Rodar processo " << "[" << min->first << "]" << " de "
				<< "[" << total_exec << "]" << " ate " << "["
				<< total_exec + min->second << "]" << endl;
			total_exec = total_exec + min->second;
			arrival.erase(min->first);
			exec.erase(min->first);
			aux_map.erase(min->first);
		}
		else
			total_exec++;
	}
	output.close();

	turnaround = (float)aux/(float)(data.size()/2); // average turnaround time
	avg_wait = (float)aux2/(float)(data.size()/2);	// average wait time
	cout << "SJF " << turnaround << " " << avg_wait << " " << avg_wait << endl; // avg_wait = avg_response
}

void ProcessManager::ScheduleProcessRR()
{
	int t_arr = 0, t_exec = 0, aux = 0, aux2 = 0, aux3 = 0, aux4 = 0, 
		t_wait = 0, quantum = 2, aux_exec = 0, swap = 0, flag = 1;
	int total_exec = 0;
	float turnaround = 0.0, avg_wait = 0.0, avg_resp = 0.0;
	fstream output;
	map<int, int> arrival;
	map<int, int> exec;

	output.open("RR.txt", fstream::in | fstream::out | fstream::trunc);

	for(int i = 0; i < data.size(); i+=2){
		t_arr = atoi(data.at(i).c_str());
		t_exec = atoi(data.at(i+1).c_str());
		arrival[i/2] = t_arr;
		exec[i/2] = t_exec;
	}

	aux4 = accumulate(arrival.begin(), arrival.end(), 0,		// sum of all arrival times
		[](const int previous, decltype(arrival)::value_type& element){ return previous + element.second; });

	map<int, int>::iterator it;
	vector<int> aux_map;
	map<int, int> wait;				// map for wait times/each proccess
	map<int, int> curr_exec_time;	// map for current execution time/each proccess
	map<int, int> exec_flags;		// set indicates proccess hasn't had CPU time yet
	map<int, int> first_exec;		// momment each proccess used the CPU for the first time
	for(it = exec.begin(); it != exec.end(); ++it){
		curr_exec_time[it->first] = 0;
		exec_flags[it->first] = 1;
		first_exec[it->first] = 0;
	}
	while(!exec.empty()){
		if(flag){ // set indicates aux_map hasen't been built yet for the first time
			for(it = arrival.begin(); it != arrival.end(); ++it){
				if(it->second <= total_exec){
					aux_map.insert(aux_map.end(), it->first);
				}
			}
		}
		flag = 0;
		if(!aux_map.empty()){	// aux_map[0] is always the proccess being used since we cicle through the proccess at index 0
			output << "Rodar processo " << "[" << aux_map[0] << "]" << " de "
				<< "[" << total_exec << "]" << " ate " << "["
				<< total_exec + (exec[aux_map[0]] < quantum ? exec[aux_map[0]] : quantum) << "]" << endl;
			wait[aux_map[0]] = (total_exec - arrival[aux_map[0]] - curr_exec_time[aux_map[0]]) < 0 ? 
				0 : (total_exec - arrival[aux_map[0]] - curr_exec_time[aux_map[0]]);
			if(exec_flags[aux_map[0]]){		// store time when proccess n first reached the CPU
				first_exec[aux_map[0]] = total_exec;
				exec_flags[aux_map[0]] = 0;
			}
			curr_exec_time[aux_map[0]] = curr_exec_time[aux_map[0]] + (exec[aux_map[0]] < quantum ? exec[aux_map[0]] : quantum);
			total_exec = total_exec + (exec[aux_map[0]] < quantum ? exec[aux_map[0]] : quantum);
			exec[aux_map[0]] = exec[aux_map[0]] - quantum;
			if(exec[aux_map[0]] <= 0){ // if proccess execution finished, remove it from aux_map
				arrival.erase(aux_map[0]);
				exec.erase(aux_map[0]);
				aux_map.erase(aux_map.begin());
			}
			else{	// else, cycle the proccess queue
				swap = aux_map[0];
				aux_map.erase(aux_map.begin());
				for(it = arrival.begin(); it != arrival.end(); ++it){
					if(it->second <= total_exec){
						if((find(aux_map.begin(), aux_map.end(), it->first) == aux_map.end()) && (it->first != swap)){
							aux_map.insert(aux_map.end(), it->first);
						}
					}
				}
				aux_map.insert(aux_map.end(), swap);
			}
		}
		else{	// if no proccess found at execution time n, increment our "clock"
			total_exec++;
			flag = 1;
		}
	}
	output.close();

	aux = accumulate(curr_exec_time.begin(), curr_exec_time.end(), 0,
		[](const int previous, decltype(arrival)::value_type& element){ return previous + element.second; });

	aux2 = accumulate(wait.begin(), wait.end(), 0,
		[](const int previous, decltype(arrival)::value_type& element){ return previous + element.second; });

	aux3 = accumulate(first_exec.begin(), first_exec.end(), 0,
		[](const int previous, decltype(arrival)::value_type& element){ return previous + element.second; });

	aux = aux + aux2;

	turnaround = (float)aux/(float)(data.size()/2); // average turnaround time
	avg_wait = (float)aux2/(float)(data.size()/2);	// average wait time
	avg_resp = (float)(aux3 - aux4)/(float)(data.size()/2); // average response
	cout << "RR " << turnaround << " " << avg_resp << " " << avg_wait << endl;
}