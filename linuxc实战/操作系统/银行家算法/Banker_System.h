#ifndef BANKER_SYSTEM_H
#define BANKER_SYSTEM_H

#include <unistd.h>
#include <set>
#include <vector>
#include <iostream>

class Process;

class System{
public:
	System(unsigned int max=0){
		setMaxAvailable(max);
		setAvailable(max);
		hMutex = CreateSemaphore(NULL, 1, 1, NULL);
	}
	void setMaxAvailable(unsigned int max);
	void setAvailable(unsigned int num);
	unsigned int getMaxAvailable(void) const;
	unsigned int getAvailable(void) const;
	unsigned int attainResource(Process *process);
	bool freeResource(Process *process);
	void printProcessList(std::ostream &os);
private:
	unsigned int maxAvailable;
	unsigned int available;
	std::set<Process*> processList;
	std::vector<unsigned int> processUid;
	HANDLE hMutex;

	bool banker(Process *process);
	void wait(void);
	void release(void);
};
#endif
