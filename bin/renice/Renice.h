#ifndef __RENICE_H
#define __RENICE_H

#include <POSIXApplication.h>

/**
 * @addtogroup bin
 * @{
 */

/**
 * Renice application.
 */
class Renice : public POSIXApplication
{
  public:

    /**
     * Class constructor.
     *
     * @param argc Argument count.
     * @param argv Argument values.
     */
    Renice(int argc, char **argv);

    /**
     * Class destructor.
     */
    virtual ~Renice();

    /**
     * Execute the application.
     *
     * @return Result code.
     */
    virtual Result exec();

  private:

    /**
     * Set the priority for a process.
     */
    Result setPriority(ProcessID pid, int priority);
};

/**
 * @}
 */

#endif /* __RENICE_H */
