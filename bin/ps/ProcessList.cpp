#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "ProcessList.h"

ProcessList::ProcessList(int argc, char *argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Output system process list");
    // Display the priority of processes
    parser().registerFlag('l', "priority", "Display priority levels of all processes");
}

ProcessList::Result ProcessList::exec()
{
    const ProcessClient proc;
    String output;

    // Display the priority if the flag is set, otherwise display as normal
    if (arguments().get("priority"))
    {
        output << "ID  PRIORITY PARENT  USER GROUP STATUS     CMD\r\n";
    }
    else
    {
        output << "ID  PARENT  USER GROUP STATUS     CMD\r\n";
    }

    // Iterate through processes
    for (ProcessID pID = 0; pID < ProcessClient::MaximumProcesses; pID++)
    {
        ProcessClient::Info pInfo;

        ProcessClient::Result res = proc.processInfo(pID, pInfo);
        if (res == ProcessClient::Success)
        {
            DEBUG("PID " << pID << " state = " << pInfo.textState);

            // Output a line
            char line[128];

            if (arguments().get("priority"))
            {
                snprintf(line, sizeof(line),
                    "%3d %8d %7d %4d %5d %10s %32s\r\n",
                     pID, pInfo.kernelState.priority, pInfo.kernelState.parent,
                     0, 0, pInfo.textState, pInfo.command);
            }
            else
            {
                snprintf(line, sizeof(line),
                    "%3d %7d %4d %5d %10s %32s\r\n",
                     pID, pInfo.kernelState.parent,
                     0, 0, pInfo.textState, pInfo.command);
            }
            output << line;
        }
    }

    write(1, *output, output.length());
    return Success;
}
