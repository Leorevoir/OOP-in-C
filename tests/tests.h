#ifndef CPLUS_OOP_TESTS_H_
#define CPLUS_OOP_TESTS_H_

#include <criterion/criterion.h>

#include <fcntl.h>
#include <unistd.h>

static int stderr_fd;

static void remove_stderr(void)
{
    int devnull = open("/dev/null", O_WRONLY);
    stderr_fd = dup(STDERR_FILENO);

    dup2(devnull, STDERR_FILENO);
    close(devnull);
}

static void restore_stderr()
{
    dup2(stderr_fd, STDERR_FILENO);
    close(stderr_fd);
}

#endif /* CPLUS_OOP_TESTS_H_ */
