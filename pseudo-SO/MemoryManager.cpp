#include "MemoryManager.h"


//Instancia a classe para o kernel passando a refer�ncia de suas fun��es
MemoryManager::MemoryManager(Kernel& kernel) : _kernel(kernel)
{
	_kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	_kernel.Load("paginate memory", [this](std::string const& ) { return this->PaginateMemoryFIFO(); });
	_kernel.Load("paginate memory", [this](std::string const& ) { return this->PaginateMemorySC(); });
	_kernel.Load("paginate memory", [this](std::string const& ) { return this->PaginateMemoryLRU(); });
};

void MemoryManager::GetDataFromBUS(std::string str)
{
	data.push_back(str);
	
}

void MemoryManager::PaginateMemoryFIFO()
{
	
	int fifo = 0, pagefault = 0;
	int aux = std::atoi(data.at(0).c_str());

	std::vector<int> frames(aux, 0);

	for (int i = 1; i<data.size(); i++)										//Percorre as entradas do arquivo
	{																		//Procura se página está nos frames
		if ((std::find(frames.begin(), frames.end(), std::atoi(data.at(i).c_str()))) == frames.end()) {
			frames[fifo] = std::atoi(data.at(i).c_str());					//Coloca página na memória conforme fifo
			fifo = (fifo + 1) % aux;										//Simula fila de fifo
			pagefault++;													//Ocorreu falta de página
		}
	}
	std::cout << "FIFO " << pagefault << std::endl;
}

void MemoryManager::PaginateMemorySC()
{

	
	int pagefault = 0;
	int max = std::atoi(data.at(0).c_str());
	int aux;
	std::vector<int> mem(max, 0);
	std::vector<frame> queue;
	int index;

	
	for (int i = 1; i < data.size(); i++)									//Percorre as entradas do arquivo
	{
		aux = std::atoi(data.at(i).c_str());
		const auto p = std::find_if(queue.begin(), queue.end(),				//Lambda gera Iterador para achar na fila uma página em que page == aux
			[aux](const frame& f) { return f.page == aux; });
		const auto r = std::find_if(queue.begin(), queue.end(),				//Lambda gera Iterador para achar na fila uma página em que bitR == false
			[aux](const frame& f) { return f.bitR == false; });
		index = r - queue.begin() - 1;

		if ((std::find(mem.begin(), mem.end(), aux)) == mem.end())			//Página não está em memória
		{
			if (p != queue.end())											//Página está na fila
			{
				if (queue.at(index).countR++ == 3)							//Incrementa contador de referência e checa
				{
					queue.at(index).bitR = false;							//Se for igual a 3 zera bit R
				}
			}
			else
			{
				if (queue.size() == max)									//Checa se fila preenchida
				{
					
					for (int j = 0; j <= max; j++)							//Percorre fila
					{
						auto it = queue.begin();							//Ponteiro para o inicio da fila
						if (it->bitR == true)								//Checa se página foi referenciada
						{

							frame f{ it->page, false, (it->countR) };		//Cópia da página
							queue.erase(it);								//Remove página da fila
							queue.push_back(f);								//joga pro final da lista com bit R zerado
						}
						else												//Página não foi referenciada
						{
							mem.at(std::distance(							//Procura posição da página antiga na memória
								mem.begin(), std::find(mem.begin(),			
									mem.end(), it->page))) = aux;			//Coloca nova página no lugar
							queue.erase(queue.begin());						//Remove página antiga da fila
							frame f{ aux, true, 1 };
							queue.push_back(f);								//Coloca página nova no final da fila
							break;
						}
					}		
				}
				else														//Fila ainda não preenchida
				{				
					frame f{ std::atoi(data.at(i).c_str()), true};			
					queue.push_back(f);										//Joga página pro final da fila
					mem[queue.size() - 1] = aux;							//coloca página na memória
				}
			}
			pagefault++;													//Ocorreu falta de página
		}
		else																//Página em Memória
		{
			if (p != queue.end())											//Página está na fila
			{
				if (queue.at(p - queue.begin()).countR++ == 3)				//Incrementa contador de referência e checa
				{
					queue.at(p - queue.begin()).bitR = false;				//Se for igual a 3 zera bit R
				}
			}
			else															//Página não está na fila
			{
				frame f{ std::atoi(data.at(i).c_str()), true, 1 };			
				queue.push_back(f);											//Coloca página no final da fila
			}
		}
	}
	std::cout << "SC " << pagefault << std::endl;
}

void MemoryManager::PaginateMemoryLRU()
{

	int pagefault = 0;
	int max = std::atoi(data.at(0).c_str());
	int aux;
	std::vector<int> mem(max, 0);
	std::vector<int> queue;

	for (int i = 1; i < data.size(); i++)									//Percorre as entradas do arquivo
	{
		aux = std::atoi(data.at(i).c_str());								//Entrada

		auto qit = std::find(queue.begin(), queue.end(), aux);				//Iterador para achar na fila uma página igual à entrada
		
		if ((std::find(mem.begin(), mem.end(), aux)) == mem.end())			//Página não está em memória
		{
			if (qit != queue.end())											//Página está na fila
			{
				mem.at(std::distance(										//Procura posição da página antiga na memória
					mem.begin(), std::find(mem.begin(), 
						mem.end(), queue.at(0)))) = aux;					//Coloca nova página no lugar
				queue.erase(queue.begin());									
				queue.erase(qit);											
				queue.push_back(aux);										//Joga página para o final da fila

			}
			else															//Página não está na fila
			{
				if (queue.size() == max)									//Checa se fila preenchida
				{
					mem.at(std::distance(									//Procura posição da página antiga na memória
						mem.begin(), std::find(mem.begin(), 
							mem.end(), queue.at(0)))) = aux;				//Coloca nova página no lugar
					queue.erase(queue.begin());
					queue.push_back(aux);									//Joga página para o final da fila

				}
				else														//Fila ainda não preenchida
				{
					queue.push_back(aux);									//Joga página pro final da fila
					mem[queue.size() - 1] = aux;							//coloca página na memória
				}
			}
			pagefault++;													//Ocorreu falta de página
		}
		else																//Página em Memória
		{
			if (qit != queue.end())											//Página está na fila
			{
				queue.erase(qit);
				queue.push_back(aux);
			}
			else															//Página não está na fila
			{
				queue.push_back(aux);										//Coloca página no final da fila
			}
		}
	}
	std::cout << "LRU " << pagefault << std::endl;
}