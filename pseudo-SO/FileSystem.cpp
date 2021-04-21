#include "FileSystem.h"

//Instancia a classe para o kernel passando a referência de suas funções
FileSystem::FileSystem(Kernel& kernel) : _kernel(kernel)
{
	_kernel.Load("read", [this](std::string const& str) { return this->ReadFile(str); });
	_kernel.Load("bus", [this](std::string const&) { return this->DataBUS(); });
};

void FileSystem::ReadFile(std::string fname)
{
	std::ifstream file(fname, std::ios::binary | std::ios::ate);
	if (file.fail()) {
		perror("File not found!");
		exit(EXIT_FAILURE);
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);
	file.read(buffer.data(), size);

	std::string aux(buffer.begin(), buffer.end());

	std::stringstream ss(aux);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	this->disk = vstrings;
}

//Transferir dados para outros módulos
void FileSystem::DataBUS()
{
	for (auto it : this->disk)
		_kernel.Run("load", it);
}

//Apenas para testes
std::vector<std::string> FileSystem::GetDataFromDisk()
{
	return this->disk;
}
