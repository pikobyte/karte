/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file utils.c
 *
 * \brief General utility functions, from logging to memory and string
 * manipulation.
 *
 * \author Anthony Mercer
 *
 */

#include "utils.h"

/* -------------------------------------------------------------------------- */
/* ARRAYS                                                                     */
/* -------------------------------------------------------------------------- */
/**
 * \desc The growth of an array involves the increasing of its size and
 * consequent reallocation. If reallocation fails, an error is issued and only
 * array header is allocated. The first calculation is the double current size,
 * which is zero if the array is NULL. The minimum required memory is the
 * current usage plus the number of required elements. A decision is then made:
 * whether the double size is greater than that required, the smaller of the two
 * is the actual required. The total space required for reallocation is the
 * number of actual required elements, multiplied by the size of object within
 * the array, plus the 2 32-bit integer header. If the reallocated memory not
 * given, an error is logged and only array header memory is allocated.
 * Otherwise, if the array is currently NULL, the number of used elements is set
 * to zero. The size of the array (number of indices) is set in the header, and
 * the pointer to the new memory data (skipping header) is returned.
 */
void *ArrayGrowBy(const void *arr, const i32 n, const i32 size) {
    const i32 dbl_cur = arr ? 2 * ArraySize(arr) : 0;
    const i32 min_req = ArrayCount(arr) + n;
    const i32 act_req = dbl_cur > min_req ? dbl_cur : min_req;
    const i32 tot_req = size * act_req + sizeof(i32) * 2;
    i32 *ptr = (i32 *)realloc(arr ? ArrayPtr(arr) : 0, tot_req);

    if (ptr) {
        if (!arr) {
            ptr[1] = 0;
        }
        ptr[0] = act_req;
        return ptr + 2;
    } else {
        Log(ERR, "Could not allocate Array of size %i!", tot_req);
        return (void *)(2 * sizeof(i32));
    }
}

/* -------------------------------------------------------------------------- */
/* I/O                                                                        */
/* -------------------------------------------------------------------------- */
/**
 * \desc Checks to see if a file with a given path exists. Note that F_OK is
 * specific to Unix systems only.
 */
bool FileExists(const char *path) { 
    // TODO: Find a non-Posix way of doing this.
#if _WIN32
    return _access(path, 0) != -1; 
#else
    return access(path, F_OK) != -1; 
#endif
}

/* -------------------------------------------------------------------------- */
/* LOGGING                                                                    */
/* -------------------------------------------------------------------------- */
/**
 * \desc Takes a log code (log, warning or error) and accompanying formatted
 * string and required parameters. The log first states the current date and
 * time, then the log code and finally the input formatted string and extra
 * parameters. If the error is fatal, then the program exits returning an error
 * code. The log is written to the stdout for logs/warnings and stderr for
 * errors/fatals.
 */
void Log(const LogCode lc, const char *str, ...) {
    char buff[512] = {0};
    char tod[32] = {0};
    char type[32] = {0};

    switch (lc) {
    case LOG:
        sprintf(type, "\x1B[1;32mKARTE LOG\x1B[0;37m");
        break;
    case WARN:
        sprintf(type, "\x1B[1;33mKARTE WRN\x1B[0;37m");
        break;
    case ERR:
        sprintf(type, "\x1B[1;31mKARTE ERR\x1B[0;37m");
        break;
    case FATAL:
        sprintf(type, "\x1B[1;45;41mKARTE FTL\x1B[0;37m");
        break;
    default:
        sprintf(type, "\x1B[1;32mKARTE LOG\x1B[0;37m");
        break;
    }

    DateAndTime(tod);

    sprintf(buff, "[%s %s] %s\n", tod, type, str);

    va_list ap;
    va_start(ap, str);
    if (lc == FATAL) {
        vfprintf(stderr, buff, ap);
        exit(EXIT_FAILURE);
    } else if (lc == ERROR) {
        vfprintf(stderr, buff, ap);
    } else {
        vfprintf(stdout, buff, ap);
    }
    va_end(ap);
}

/* -------------------------------------------------------------------------- */
/* MEMORY                                                                     */
/* -------------------------------------------------------------------------- */
/**
 * \desc Allocates zero-initialised memory based on a chosen size. If the memory
 * is not allocated by the operating system, the program exits. Otherwise the
 * number of global memory allocations is increased, and a pointer to the start
 * of the allocated memory is returned.
 */
void *Allocate(const size_t size) {
    void *mem = calloc(1, size);
    if (mem == NULL) {
        Log(FATAL, "Could not allocate memory of size %i!", size);
    }

    g_mem_allocs++;
    return mem;
}

/**
 * \desc Checks to see if the memory is first valid, and if it is, then it is
 * freed and the number of global memory allocations is decreased. Otherwise,
 * the program produces an error. The program need not exit as it can continue
 * normally.
 */
void Free(void *mem) {
    if (mem == NULL) {
        Log(ERR, "Could not free memory at %p!", mem);
        return;
    }

    free(mem);
    mem = NULL;
    g_mem_allocs--;
}

/* -------------------------------------------------------------------------- */
/* MISCELLANEOUS                                                              */
/* -------------------------------------------------------------------------- */
/**
 * \desc Takes a destination buffer to which the current date and time is copied
 * to in a YY/MM/DD hr/min/sec format.
 */
void DateAndTime(char *dest) {
    char buff[27] = {0};
    struct tm *tm_info = NULL;
    time_t timer = {0};
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buff, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    strcpy(dest, buff);
}