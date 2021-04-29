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

struct frame
{
	int page;
	bool bitR = false;
	int countR = 1;
};

void MemoryManager::PaginateMemoryFIFO()
{
	
	int fifo = 0, pagefault = 0;
	int aux = std::atoi(data.at(0).c_str());

	std::vector<int> frames(aux, 0);

	for (int i = 1; i<data.size(); i++)
	{
		if ((std::find(frames.begin(), frames.end(), std::atoi(data.at(i).c_str()))) == frames.end()) {
			frames[fifo] = std::atoi(data.at(i).c_str());
			fifo = (fifo + 1) % aux;
			pagefault++;
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
	std::vector<frame> frames;
	int index;
	bool found;
	//std::vector<int> bitR;
	/*
	const auto p = std::find_if(frames.begin(), frames.end(),s
		[](const frame& x) { return x.page == 1 });
	if (p != frames.end()) frames.erase(p);

	std::cout << "asd " << frames[0].page << std::endl;
	*/
	
	for (int i = 1; i < data.size(); i++)
	{
		found = false;
		aux = std::atoi(data.at(i).c_str());
		const auto p = std::find_if(frames.begin(), frames.end(),			//Iterador para achar frame em que page == aux
			[aux](const frame& f) { return f.page == aux; });
		const auto r = std::find_if(frames.begin(), frames.end(),			//Iterador para achar frame em que birR == false
			[aux](const frame& f) { return f.bitR == false; });
		index = r - frames.begin() - 1;
		for (auto it = mem.begin(); it != mem.end(); it++)
			std::cout << *it << std::endl;
		if ((std::find(mem.begin(), mem.end(), aux)) == mem.end())
		{
			if (p != frames.end())
			{
				if (frames.at(index).countR++ == 3)
				{
					frames.at(index).bitR = false;
				}
			}
			else
			{
				if (frames.size() == max)
				{
					
					for (int j = 0; j <= max; j++)
					{
						auto it = frames.begin();
						if (it->bitR == true)
						{
							frame f{ it->page, false, it->countR };
							frames.erase(it);
							frames.push_back(f);
						}
						else
						{
							mem.at(std::distance(mem.begin(), std::find(mem.begin(), mem.end(), it->page))) = aux;
							frames.erase(frames.begin());
							frame f{ aux, true };
							frames.push_back(f);
							break;
						}
					}		
				}
				else
				{
					frame f{ std::atoi(data.at(i).c_str()), true};
					frames.push_back(f);
					mem[frames.size() - 1] = aux;
				}
			}
			pagefault++;
		}
		else
		{
			if (p != frames.end())
			{
				if (frames.at(p - frames.begin()).countR++ == 3)
				{
					frames.at(p - frames.begin()).bitR = false;
				}
			}
			else
			{
				frame f{ std::atoi(data.at(i).c_str()), true };
				frames.push_back(f);
			}
		}
	}
	std::cout << "SC " << pagefault << std::endl;
}

void MemoryManager::PaginateMemoryLRU()
{

	int fifo = 0, pagefault = 0;
	int aux = std::atoi(data.at(0).c_str());

	std::vector<int> frame(aux, 0);

	for (int i = 1; i < data.size(); i++)
	{
		if ((std::find(frame.begin(), frame.end(), std::atoi(data.at(i).c_str()))) == frame.end()) {
			frame[fifo] = std::atoi(data.at(i).c_str());
			fifo = (fifo + 1) % aux;
			pagefault++;
		}
	}
	std::cout << "LRU " << pagefault << std::endl;
}