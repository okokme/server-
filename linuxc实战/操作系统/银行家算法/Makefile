CC = g++
CXXFLAGS= -g
target:Banker.cpp Banker_Process.o Banker_System.o
	$(CC) Banker.cpp Banker_System.o Banker_Process.o -o Bankertest $(CXXFLAGS)
Banker_Process.o:Banker_Process.cpp 
	$(CC) -c Banker_Process.cpp $(CXXFLAGS)
Banker_System.o:Banker_System.cpp
	$(CC) -c Banker_System.cpp $(CXXFLAGS)

clean:
	rm *.o