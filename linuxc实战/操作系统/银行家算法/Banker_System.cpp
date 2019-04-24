#include "Banker_System.h"
#include "Banker_Process.h"
#include <iostream>
#include <string>
#include <unistd.h>

void System::setMaxAvailable(unsigned int max)
{
	maxAvailable = max > 0 ? max : 0;
}

void System::setAvailable(unsigned int num)
{
	available = num > 0 ? num : 0;
}

unsigned int System::getMaxAvailable(void) const
{
	return maxAvailable;
}

unsigned int System::getAvailable(void) const
{
	return available;
}

void System::wait(void)
{
	WaitForSingleObject(hMutex,INFINITE);
}

void System::release(void)
{
	ReleaseSemaphore(hMutex, 1, NULL);
}

void System::printProcessList(std::ostream &os)
{

	for(auto first = processUid.begin(); first != processUid.end(); ++first)
	{
		os << *first << " ";
	}
	os << "\r\n";
}

unsigned int System::attainResource(Process *process)
{
	wait();

	int rtn = 0;
	unsigned int requestNum = process->getRequestNeed();
	unsigned int available_bk = getAvailable();
	unsigned int ownNeed_bk = process->getOwnNeed();
	std::string prompt;

	if(requestNum <= getAvailable())
	{
		setAvailable(getAvailable() - requestNum);
		process->setOwnNeed(process->getOwnNeed() + requestNum);

		prompt = prompt +  "\nsystem" + "\t" + std::to_string(available_bk) + '\n';
		std::cout << prompt;

		prompt.clear();

		if(banker(process))
		{
			processList.insert(process);

			prompt = prompt +  "Thread" + "\t" + std::to_string(process->getUid())  + "\t" + std::to_string(process->getMaxNeed()) + "\t" 
			 	+ std::to_string(process->getOwnNeed()) + "\t" + std::to_string(process->getRequestNeed()) + "\t" + "Success\n";
			std::cout << prompt;
			rtn = 0;
		}
		else
		{
			setAvailable(available_bk);
			process->setOwnNeed(ownNeed_bk);

			prompt = prompt +  "Thread" + "\t" + std::to_string(process->getUid())  + "\t" + std::to_string(process->getMaxNeed()) + "\t" 
			 	+ std::to_string(process->getOwnNeed()) + "\t" + std::to_string(process->getRequestNeed()) + "\t" + "Failure\n";
			std::cout << prompt;

			rtn = 1;
		}
		printProcessList(std::cout);
	}
	else
	{
		rtn = 1;
	}

	release();
	return rtn;
}

bool System::banker(Process *process)
{
	bool rtn;
	unsigned int available_bk = getAvailable();
	unsigned int num = process->getRequestNeed();

	processUid.clear();

	for(auto i = processList.begin(); i != processList.end(); )
	{
		if(false == (*i)->isFinish() && (*i)->getMaxNeed() - (*i)->getOwnNeed() <= getAvailable())
		{
			(*i)->setFinish(true);
			setAvailable(getAvailable()+(*i)->getOwnNeed());
			processUid.push_back((*i)->getUid());
			i = processList.begin();
		}
		else
		{
			++i;
		}
	}
	rtn = true;
	for(auto i = processList.begin(); i != processList.end(); ++i)
	{
		if((*i)->isFinish() == false)
			rtn = false;
		(*i)->setFinish(false);
	}
	setAvailable(available_bk);
	return rtn;
}


bool System::freeResource(Process *process)
{
	wait();

	bool rtn;
	if(processList.find(process) == processList.end())
		rtn = false;
	else
		rtn = true;
	setAvailable(getAvailable() + process->getOwnNeed());
	processList.erase(process);

	release();
	return rtn;
}