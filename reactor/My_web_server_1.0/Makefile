CC = g++
CXXFLAGS= -g -lpthread

target:server.cpp webServer.o task.o
	$(CC) server.cpp webServer.o task.o -o server $(CXXFLAGS)
webServer.o:webServer.cpp
	$(CC) -c webServer.cpp $(CXXFLAGS)
task.o:task.cpp
	$(CC) -c task.cpp $(CXXFLAGS)
clean:
	rm *.o
# 删除.o文件 make clean