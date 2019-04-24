#ifndef BANKER_PROCESS
#define BANKER_PROCESS

#include "Banker_Process.h"
#include "Banker_System.h"
#include <unistd.h>
#include <iostream>

using namespace std;

extern HANDLE g_mutex;

void Process::setMaxNeed(unsigned int max)
{
	maxNeed = max;
}

void  Process::setOwnNeed(unsigned int own)
{
	ownNeed = own;
}

unsigned int  Process::getMaxNeed(void) const
{
	return maxNeed;
}

unsigned int  Process::getOwnNeed(void) const
{
	return ownNeed;
}

bool Process::isFinish(void)
{
	return finish;
}

void Process::setFinish(bool f)
{
	finish = f;
}

void Process::setUid(unsigned int u)
{
	uid = u;
}

unsigned int Process::getUid(void)
{
	return uid;
}

unsigned int Process::getRequestNeed(void)
{
	return requestNeed;
}

bool Process::setRequestNeed(unsigned int r)
{
	bool rtn = false;

	if(r <= getMaxNeed() - getOwnNeed())
	{
		requestNeed = r;
		rtn = true;
	}
	return rtn;
}



bool  Process::requestResource(unsigned int num, System &s)
{
	bool rtn = false;
	int res = 0;

	if(num <= getMaxNeed() - getOwnNeed())
	{
		if (!setRequestNeed(num))
			return false;

		res = s.attainResource(this);
		
		switch (res)
		{
		case 0:
			rtn = true;
			break;
		case 1:
			rtn = false;
			break;
		}
	}
	return rtn;
}

bool Process::freeSource(System &s)
{
	s.freeResource(this);
	return true;
}
#endif
