#include <unistd.h>
// #include <process.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "Banker_Process.h"
#include "Banker_System.h"

#define MAX_THREAD 64
#define MAX_AVAILABLE 200000

typedef struct Param
{
	System *system;
	int uid;
}Param;

unsigned int __stdcall myThread(void *param)
{
	unsigned int need = GetCurrentThreadId();
	Param *pa = static_cast<Param*>(param);

 	srand(need);
 	do{
 		need = rand() % MAX_AVAILABLE;
 	}while(need == 0);

	Process pro(need,0,pa->uid);
	
	while(pro.getOwnNeed() < pro.getMaxNeed())
	{
		unsigned int resource = 0;

		do{
			if(pro.getMaxNeed() - pro.getOwnNeed() > 1)
				resource = rand()% (pro.getMaxNeed() - pro.getOwnNeed());
			else
				resource = 1;
		}while(resource == 0);

		bool res = pro.requestResource(resource,*(pa->system));
	}

	std::string prompt;
	prompt = prompt +  "\n~~~~~~Thread\t" + std::to_string(pa->uid) + "(" + std::to_string(pro.getMaxNeed()) + ")" + " has request success! now free source\n";
	std::cout << prompt;

	pro.freeSource(*(pa->system));
	return 0;
}

int main(int argc, char const *argv[])
{
	HANDLE hThread[MAX_THREAD];
	System s(MAX_AVAILABLE);
	Param par[MAX_THREAD];

	for(int i=0; i < MAX_THREAD; ++i)
	{
		par[i].system = &s;
		par[i].uid = i;
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, myThread, par + i, 0, NULL);
	}
	
	WaitForMultipleObjects(MAX_THREAD, hThread, TRUE, INFINITE);

	for(int i = 0; i< MAX_THREAD; ++i)
	{
		CloseHandle(hThread[i]);
	}
	return 0;
}