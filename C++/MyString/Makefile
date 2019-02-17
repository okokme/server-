CC = g++
CXXFLAGS= -g
target:MyString_test.cpp MyString.o
	$(CC) MyString_test.cpp MyString.o -o MyString_test $(CXXFLAGS)
MyString.o:MyString.cpp
	$(CC) -c MyString.cpp $(CXXFLAGS)
clean:
	rm *.o
