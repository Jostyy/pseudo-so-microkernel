all: pseudoso

FileSystem.o:
	g++ -g -c -std=c++14 FileSystem.cpp

CheckArgs.o:
	g++ -g -c -std=c++14 CheckArgs.cpp

IOManager.o:
	g++ -g -c -std=c++14 IOManager.cpp

ProcessManager.o: 
	g++ -g -c -std=c++14 ProcessManager.cpp

Kernel.o: 
	g++ -g -c -std=c++14 Kernel.cpp

MemoryManager.o: 
	g++ -g -c -std=c++14 MemoryManager.cpp

pseudoso: FileSystem.o CheckArgs.o IOManager.o ProcessManager.o Kernel.o MemoryManager.o pseudo-SO.cpp
	g++ -Wall -o pseudoso FileSystem.o CheckArgs.o IOManager.o ProcessManager.o Kernel.o MemoryManager.o pseudo-SO.cpp
	rm FileSystem.o CheckArgs.o IOManager.o ProcessManager.o Kernel.o MemoryManager.o

clean: 
	rm pseudoso