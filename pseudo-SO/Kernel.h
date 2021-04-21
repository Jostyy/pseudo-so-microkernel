#ifndef Kernel_h
#define Kernel_h
#include <unordered_map>
#include <vector>
#include <functional>

using ScriptFunction = std::function<void(std::string const&)>;
using Script_map = std::unordered_map<std::string, std::vector<ScriptFunction>>;

class Kernel
{
private:

	Script_map system;

public:

	void Load(std::string const& event_type, ScriptFunction handler);
	void Run(std::string, std::string);
	void Run(std::string);
};

#endif