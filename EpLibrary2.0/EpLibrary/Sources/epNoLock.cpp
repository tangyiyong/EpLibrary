/*! 
NoLock for the EpLibrary
Copyright (C) 2012  Woong Gyu La <juhgiyo@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "epNoLock.h"
#include "epSystem.h"
#include "epException.h"
using namespace epl;


NoLock::NoLock() :BaseLock()
{
}
NoLock::NoLock(const NoLock& b):BaseLock()
{}

NoLock::~NoLock()
{
}

void NoLock::Lock()
{
#if _DEBUG
	std::vector<int>::iterator iter;
	int threadID=GetCurrentThreadId();
	for(iter=m_threadList.begin();iter!=m_threadList.end();iter++)
	{
		EP_VERIFY_THREAD_DEADLOCK_ERROR(*iter!=threadID);
	}
#endif //_DEBUG
#if _DEBUG
	m_threadList.push_back(threadID);
#endif //_DEBUG
}

long NoLock::TryLock()
{
#if _DEBUG
	std::vector<int>::iterator iter;
	int threadID=GetCurrentThreadId();
	for(iter=m_threadList.begin();iter!=m_threadList.end();iter++)
	{
		EP_VERIFY_THREAD_DEADLOCK_ERROR(*iter!=threadID);
	}
	m_threadList.push_back(threadID);
#endif //_DEBUG
	return 1;
}
long NoLock::TryLockFor(const unsigned int dwMilliSecond)
{
#if _DEBUG
	std::vector<int>::iterator iter;
	int threadID=GetCurrentThreadId();
	for(iter=m_threadList.begin();iter!=m_threadList.end();iter++)
	{
		EP_VERIFY_THREAD_DEADLOCK_ERROR(*iter!=threadID);
	}
	m_threadList.push_back(threadID);
#endif //_DEBUG
	return 1;	
}
void NoLock::Unlock()
{
#if _DEBUG
	std::vector<int>::iterator iter;
	int threadID=GetCurrentThreadId();
	for(iter=m_threadList.begin();iter!=m_threadList.end();iter++)
	{
		if(*iter==threadID)
		{
			m_threadList.erase(iter);
			break;
		}
	}
#endif //_DEBUG
}
