CC = g++
CXXFLAGS= -g -lpthread

target:FF.cpp BlockJob.o 
	$(CC) FF.cpp BlockJob.o -o  $(CXXFLAGS)
BockJob.o: BlockJob.cpp
	$(CC) -c BlockJob.cpp $(CXXFLAGS)
clean:
	rm *.o