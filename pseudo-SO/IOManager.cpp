#include "IOManager.h"

//Instancia a classe para o kernel passando a referência de suas funções
IOManager::IOManager(Kernel& kernel) : _kernel(kernel)
{
	 _kernel.Load("load", [this](std::string const& str) { return this->GetDataFromBUS(str); });
	_kernel.Load("schedule disk FCFS", [this](std::string const&) { return this->ScheduleDiskFCFS(); });
	_kernel.Load("schedule disk SSF", [this](std::string const&) { return this->ScheduleDiskSSF(); });
	_kernel.Load("schedule disk SCAN", [this](std::string const&) { return this->ScheduleDiskSCAN(); });
};
//TODO: o gerenciador de entrada/saída deve ser responsável
//por administrar o algoritmo especificado para a busca em disco
void IOManager::GetDataFromBUS(std::string str)
{
	rawData.push_back(str);
	
}

void IOManager::Setup()
{
	cilinders = atoi(rawData[0].c_str());			//Guardo o primeiro elemento do vetor de entrada, convertido para int, em cilinders, o segundo em startingPos e o resto é convertido
	startingPos = atoi(rawData[1].c_str());			// e transferido para um novo vetor. Desta forma, o novo vetor contém apenas inteiros, e de uma maneira mais familiar para tratá-los
	for(int i = 2; i < rawData.size(); i++)			//o número de cilindros e a posição atual serão utilizadas pelas funções da classe, mas apenas esta função as altera.
	{		
		data.push_back(atoi(rawData[i].c_str())); 
	}
}

void IOManager::ScheduleDiskFCFS()					//O algoritmo FCFS(First Come First Served) funciona como uma simples fila: a cabeça do disco deve ir para cada cilindro na ordem
{													//em que chegaram.
													 
	this->Setup();
	int result = 0;
	int current = startingPos;

	for(int i : data)								//result guarda quantos cilindros foram percorridos, e é incrementado pelo módulo da subtração da posição atual(current) pelo próximo
	{												//elemento da fila (i). Após isto, a posição atual é atualizada.
		result += abs(current - i);					
		current = i;
	}

	std::cout << "FCFS " << result << std::endl;
}

void IOManager::ScheduleDiskSSF()					//O algoritmo SSF(Shortest Seek First) funciona de modo que cada seek feito seja o de menor distância possível naquele momento.
{													//Novamente, result guarda quantos cilindros foram percorridos até o momento, e current guarda a posição atual da cabeça.
	this->Setup();
	int result = 0;
	int current = startingPos;
	int shortestMove = cilinders + 1;				//shortestMove indica o tamanho do menor percorrimento visto até agora. É inicializado como o número de cilindros + 1 para que a primeira
	int target = 0;									//comparação sempre a substitua, já que é impossível que um único seek precise percorrer mais cilindros do que há no disco.

													//target indica a posição no vetor de dados onde está o pedido de menor percorrimento.

	while(data.size() > 0)
	{
		for(int i = 0; i < data.size(); i++)
		{
			if(abs(current - data[i]) < shortestMove)	//Ao invés de apenas percorrer o vetor data uma vez, precisamos fazer isto múltiplas vezes. Em cada percorrimento, procuramos pelo
			{											//seek que resulte no menor percorrimento. Quando terminamos de percorrer, efetuamos o movimento incrementando result,
				shortestMove = abs(current - data[i]);	//atualizamos current, removemos o pedido da lista e reiniciamos o processo novamente. Fazemos tudo isto até que a lista de pedidos esteja vazia.
				target = i;								
			}
		}
		result += shortestMove;
		current = data[target];
		data.erase(data.begin() + target);
		target = 0;
		shortestMove = cilinders + 1;
	}

	std::cout << "SSF " << result << std::endl;
}

void IOManager::ScheduleDiskSCAN()								//O algoritmo SCAN funciona de forma similar ao SSF, mas primeiramente considerando apenas os pedidos que levem
{																//a cabeça de leitura/escrita na mesma direção que já está indo, escolhendo entre estes de acordo com SSF,
																//até que não hajam mais pedidos deste tipo, a partir de onde vamos até a ponta do disco, e agimos como um SSF normal até que não hajam mais pedidos.
	
	this->Setup();
	int result = 0;
	bool goingDown = true;
	int current = startingPos;
	int shortestMove = cilinders + 1;					
	int target = 0;

	while(goingDown)
	{
		for(int i = 0; i < data.size(); i++)
		{
			if( (data[i] < current) && ( abs(current - data[i]) < shortestMove) ) 	//A implementação é similar a do SSF, exceto que para a primeira passagem, para que um pedido seja considerado,
			{ 																		//seu valor deve ser menor do que o da posição atual da cabeça.
				target = i;															
				shortestMove = abs(current - data[i]);
			}
		}

		if(shortestMove == (cilinders + 1))					//Aqui usamos uma conveniência da implementação do SSF. Se após percorrer todo o vetor data, shortestMove ainda for o valor impossível,
		{													//isso indica que chegamos ao extremo dos pedidos nesta direção, então devemos mover a cabeça até a ponta. Representamos isto incrementando result e setando current para 0.
			goingDown = false;								
			result += current;
			current = 0;
			break;
		}

		result += shortestMove;
		current = data[target];
		data.erase(data.begin() + target);
		target = 0;
		shortestMove = cilinders + 1;
	}

	while(data.size() > 0)
	{
		for(int i = 0; i < data.size(); i++)
		{
			if(abs(current - data[i]) < shortestMove)
			{
				shortestMove = abs(current - data[i]);
				target = i;
			}
		}
		result += shortestMove;
		current = data[target];
		data.erase(data.begin() + target);
		target = 0;
		shortestMove = cilinders + 1;
	}

	std::cout << "SCAN " << result << std::endl;

}