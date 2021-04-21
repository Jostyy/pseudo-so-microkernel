#include "CheckArgs.h"

//Checa se os argumentos são válidos
int CheckArgs::IsValid(int argc, char* argv[])
{
	if (argc != 3)
		throw std::invalid_argument("Invalid arguments: file must be .txt!");
	std::string aux = argv[2];
	aux = aux.length() > 4 ? aux.substr(aux.length() - 4, aux.length()) : "";
	if (aux == ".txt")
		return (int)(argv[1][0] - '0');

	throw std::invalid_argument("Invalid arguments: file must be .txt!");
}