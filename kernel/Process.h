#ifndef __PROCESS_H
#define __PROCESS_H

#include <FreeNOS/API.h>
#include <Types.h>
#include "MemoryMap.h"
#include "MemoryContext.h"
#include "ProcessShares.h"
#include "Channel.h"
#include "Timer.h"

class Process
{
public:
	enum State
	{
    	Ready = 0,
    	Stopped,
    	Sleeping,
    	Waiting
	};

	enum Result
	{
    	Success = 0,
    	InvalidArgument,
    	OutOfMemory,
    	IOError,
    	WakeupPending
	};
    
	typedef u8 PriorityLevel;

	static const PriorityLevel MinPriority = 1;
	static const PriorityLevel MaxPriority = 5;
	static const PriorityLevel DefaultPriority = 3;




	Process(ProcessID id, Address entry, bool privileged, const MemoryMap &map, PriorityLevel priority = DefaultPriority);

	virtual ~Process();

	ProcessID getID() const;

	ProcessID getParent() const;

	ProcessID getWait() const;

	uint getWaitResult() const;

	State getState() const;

	ProcessShares & getShares();

	const Timer::Info & getSleepTimer() const;

	MemoryContext * getMemoryContext();

	bool isPrivileged() const;

	PriorityLevel getPriorityLevel() const;

	void setPriorityLevel(PriorityLevel prioritylevel);

	void setParent(ProcessID id);

	Result wait(ProcessID id);

	Result join(const uint result);

	Result stop();

	Result resume();

	Result raiseEvent(const ProcessEvent *event);

	Result initialize();

	Result wakeup();

	Result sleep(const Timer::Info *timer, bool ignoreWakeups = false);

	bool operator==(Process *proc);

private:
	ProcessID m_id;
	MemoryMap m_map;
	ProcessShares m_shares;
	State m_state;
	ProcessID m_parent;
	ProcessID m_waitId;
	uint m_waitResult;
	ulong m_wakeups;
	Address m_entry;
	bool m_privileged;
	MemoryContext *m_memoryContext;
	Channel *m_kernelChannel;
	Timer::Info m_sleepTimer;
	PriorityLevel m_priority;
};

#endif /* __PROCESS_H */

