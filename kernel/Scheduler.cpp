#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    Size totalCount = 0;
    for (int i = 0; i < NUM_QUEUES; i++)
    {
        totalCount += m_queues[i].count();
    }
    return totalCount;
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    int priority = static_cast<int>(proc->getPriority());
    if (priority >= 1 && priority <= NUM_QUEUES)
    {
        m_queues[priority - 1].push(proc);
        return Success;
    }

    return InvalidArgument;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    int priority = static_cast<int>(proc->getPriority());
    if (priority >= 1 && priority <= NUM_QUEUES)
    {
        Queue<Process *, MAX_PROCS> &queue = m_queues[priority - 1];
        Size count = queue.count();

        // Traverse the Queue to remove the Process
        for (Size i = 0; i < count; i++)
        {
            Process *p = queue.pop();

            if (p == proc)
                return Success;
            else
                queue.push(p);
        }
    }

    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process *Scheduler::select()
{
    for (int i = NUM_QUEUES - 1; i >= 0; i--)
    {
        if (m_queues[i].count() > 0)
        {
            Process *p = m_queues[i].pop();
            m_queues[i].push(p);
            return p;
        }
    }
    return (Process *) NULL;
}
