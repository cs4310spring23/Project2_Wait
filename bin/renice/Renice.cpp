#include <ProcessClient.h>
#include <sys/renice.h>
#include <stdlib.h>
#include <stdio.h>
#include <Process.h>
#include <FreeNOS/Kernel.h>
#include "ProcessManager.h"
#include <unistd.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Change the priority of a process");
    parser().registerPositional("PID", "Process ID to change priority", 0);
    parser().registerPositional("PRIORITY", "New priority level", 0);
}

Renice::~Renice()
{
}

Renice::Result Renice::setPriority(ProcessID pid, int priority)
{
    ProcessClient process;

    if (process.setPriority(pid, priority) != ProcessClient::Success)
    {
        ERROR("Failed to set priority for PID " << pid);
        return IOError;
    }

    return Success;
}

Renice::Result Renice::exec()
{
    ProcessID pid;
    int priority;

    pid = atoi(arguments().get("PID"));
    priority = atoi(arguments().get("PRIORITY"));

    return setPriority(pid, priority);
}
