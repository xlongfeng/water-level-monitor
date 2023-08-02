// Support files for GNU libc. Files in the system namespace go here.

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <time.h>

// #undef errno
extern int errno;
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

register char *stack_ptr asm("sp");

char *__env[1] = { 0 };
char **environ = __env;

void initialise_monitor_handles() {}

int _getpid(void) { return 1; }

int _kill(int, int)
{
    errno = EINVAL;
    return -1;
}

void _exit(int status)
{
    _kill(status, -1);
    while (1) {}
}

__attribute__((weak)) int _read(int, char *ptr, int len)
{
    for (int i = 0; i < len; ++i) { *ptr++ = static_cast<char>(__io_getchar()); }
    return len;
}

__attribute__((weak)) int _write(int, char *ptr, int len)
{
    for (int i = 0; i < len; ++i) { __io_putchar(*ptr++); }
    return len;
}

caddr_t _sbrk(int incr)
{
    extern char end asm("end");
    static caddr_t heap_end = &end;
    caddr_t prev_heap_end;

    prev_heap_end = heap_end;
    if (heap_end + incr > stack_ptr) {
        // write(1, "Heap and stack collision\n", 25);
        // abort();
        errno = ENOMEM;
        return reinterpret_cast<caddr_t>(-1);
    }

    heap_end += incr;

    return prev_heap_end;
}

int _close(int) { return -1; }

int _fstat(int, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int) { return 1; }

int _lseek(int, int, int) { return 0; }

int _open(char *, int, ...) { return -1; }

int _wait(int *)
{
    errno = ECHILD;
    return -1;
}

int _unlink(char *)
{
    errno = ENOENT;
    return -1;
}

int _times(struct tms *) { return -1; }

int _stat(char *, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _link(char *, char *)
{
    errno = EMLINK;
    return -1;
}

int _fork(void)
{
    errno = EAGAIN;
    return -1;
}

int _execve(char *, char **, char **)
{
    errno = ENOMEM;
    return -1;
}