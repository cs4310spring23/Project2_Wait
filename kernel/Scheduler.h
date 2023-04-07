#ifndef __KERNEL_SCHEDULER_H
#define __KERNEL_SCHEDULER_H
#ifndef __ASSEMBLER__

#include <Vector.h>
#include <Macros.h>
#include <Queue.h>
#include "Process.h"
#include "ProcessManager.h"

/**
 * @addtogroup kernel
 * @{
 */

/**
 * Responsible for deciding which Process may execute on the local Core.
 */
class Scheduler
{
  public:

    /**
     * Result code
     */
    enum Result
    {
        Success,
        InvalidArgument
    };

  public:

    /**
     * Constructor function.
     */
    Scheduler();

    /**
     * Get number of processes on the schedule
     *
     * @return Number of processes on the schedule
     */
    Size count() const;

    /**
     * Add a Process to the run schedule.
     *
     * @param proc Process pointer
     * @param ignoreState True to not check for the Process state prior to dequeue.
     *
     * @return Result code
     */
    Result enqueue(Process *proc, bool ignoreState);

    /**
     * Remove a Process from the run schedule.
     *
     * @param proc Process pointer
     * @param ignoreState True to not check for the Process state prior to dequeue.
     *
     * @return Result code
     */
    Result dequeue(Process *proc, bool ignoreState);

    /**
     * Select the next process to run.
     *
     * @return Process pointer or NULL if no matching process found
     */
    Process * select();

  private:

    /** Number of queues */
    static const int NUM_QUEUES = 5;

    /** Contains processes ready to run */
    Queue<Process *, MAX_PROCS> m_queues[NUM_QUEUES];
};

/**
 * @}
 */

#endif /* __ASSEMBLER__ */
#endif /* __KERNEL_SCHEDULER_H */
