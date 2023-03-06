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

#include "core/utils.h"
#include "core/common.h"

/* -------------------------------------------------------------------------- */
/* I/O                                                                        */
/* -------------------------------------------------------------------------- */
/**
 * \desc Checks to see if a file with a given path exists. Note that F_OK is
 * specific to Unix systems only.
 */
[[nodiscard]] bool FileExists(const char* path)
{
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

/*
 * FIXME: Occasional segmentation faults in here when on Windows.
 */
void Log(LogCode lc, const char* str, ...)
{
    char buff[512] = {0};
    char tod[32] = {0};
    char type[32] = {0};

    switch (lc)
    {
    case LOG_NOTIFY:
        sprintf(type, "KARTE LOG");
        break;
    case LOG_WARNING:
        sprintf(type, "KARTE WRN");
        break;
    case LOG_ERROR:
        sprintf(type, "KARTE ERR");
        break;
    case LOG_FATAL:
        sprintf(type, "KARTE FTL");
        break;
    default:
        sprintf(type, "KARTE LOG");
        break;
    }

    DateAndTime(tod);

    sprintf(buff, "[%s %s] %s\n", tod, type, str);

    va_list ap;
    va_start(ap, str);
    if (lc == LOG_FATAL)
    {
        vfprintf(stderr, buff, ap);
        exit(EXIT_FAILURE);
    }
    else if (lc == LOG_ERROR)
    {
        vfprintf(stderr, buff, ap);
    }
    else
    {
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
void* Allocate(size_t size)
{
    void* mem = calloc(1, size);
    if (mem == NULL)
    {
        Log(LOG_FATAL, "Could not allocate memory of size %i!", size);
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
void Free(void* mem)
{
    if (mem == NULL)
    {
        Log(LOG_ERROR, "Could not free memory at %p!", mem);
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
void DateAndTime(char* dest)
{
    char buff[27] = {0};
    struct tm* tm_info = NULL;
    time_t timer = {0};
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buff, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    strcpy(dest, buff);
}

/**
 * \desc Searches through a string and checks whether a character exists within
 * it.
 */
[[nodiscard]] bool StringContains(const char* str, char search)
{
    for (size_t i = 0; i < strlen(str); ++i)
    {
        if ((char)str[i] == search)
        {
            return true;
        }
    }

    return false;
}

/**
 * \desc Checks against the value to see if it is: firstly less than 2, meaning
 * it is not prime; secondly equal to 3 and hence prime; thirdly is equal to an
 * even number thus not prime; and finally iterates from 3 up to the square root
 * of the value, and if the value is cleanly divisible by any of the iterants,
 * shows that the value is not prime.
 */
[[nodiscard]] i32 IsPrime(u32 value)
{
    if (value < 2)
    {
        return false;
    }

    if (value == 3)
    {
        return true;
    }

    if ((value % 2) == 0)
    {
        return false;
    }

    for (i32 i = 3; i < floor(sqrt((f64)value)) - 1; i += 2)
    {
        if ((value % i) == 0)
        {
            return false;
        }
    }

    return true;
}

/**
 * \desc Increments the value passed in and checks if the incremented value is a
 * prime. Only when the value is prime does it return that value.
 */
[[nodiscard]] u32 NextPrime(u32 value)
{
    while (!IsPrime(value))
    {
        value++;
    }

    return value;
}

/**
 * \desc Returns the truth value of a 32-bit integer masked with a bit-field.
 */
[[nodiscard]] bool Mask32(i32 src, i32 mask) { return ((src & mask) == mask); }

/**
 * \desc Returns the truth value of a 64-bit integer masked with a bit-field.
 */
[[nodiscard]] bool Mask64(i64 src, i64 mask) { return ((src & mask) == mask); }