all: pseudoso

FileSystem.o:
	g++ -g -c -std=c++11 FileSystem.cpp

CheckArgs.o:
	g++ -g -c -std=c++11 CheckArgs.cpp

IOManager.o:
	g++ -g -c -std=c++11 IOManager.cpp

ProcessManager.o: 
	g++ -g -c -std=c++11 ProcessManager.cpp

Kernel.o: 
	g++ -g -c -std=c++11 Kernel.cpp

MemoryManager.o: 
	g++ -g -c -std=c++11 MemoryManager.cpp

pseudoso: FileSystem.o CheckArgs.o IOManager.o ProcessManager.o Kernel.o MemoryManager.o pseudo-SO.cpp
	g++ -Wall -o pseudoso FileSystem.o CheckArgs.o IOManager.o ProcessManager.o Kernel.o MemoryManager.o pseudo-SO.cpp
	rm FileSystem.o CheckArgs.o IOManager.o ProcessManager.o Kernel.o MemoryManager.o

clean: 
	rm pseudoso