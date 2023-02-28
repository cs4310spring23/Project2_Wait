#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a background process to finish");
    parser().registerPositional("PID", "Process ID of the background process to wait for");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    // Get the PID of the process to wait for
    int pid = atoi(arguments().get("PID"));
    if (pid <= 0)
    {
        ERROR("invalid PID `" << arguments().get("PID") << "'");
        return InvalidArgument;
    }

    // Wait for the process to finish
    int status;
    pid_t result = waitpid((pid_t)pid, &status, 0);

    if ((int)result == -1) {
        ERROR("failed to wait for process with PID " << pid << ": " << strerror(errno));
        return IOError;
    }

    return Success;
}
