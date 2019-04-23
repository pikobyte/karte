/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file inlines.h
 * \brief Declaration and implementation of general inline functions.
 *
 * \author Anthony Mercer
 *
 */

#ifndef INLINES_H
#define INLINES_H

#include "definitions.h"

static inline void TimeOfDay(char *dest);

enum LogCode { LOG, ERROR, WARNING };

/* -------------------------------------------------------------------------- */
/* LOGGING                                                                    */
/* -------------------------------------------------------------------------- */
static inline void Log(const enum LogCode lc, const char *str, ...) {
    char buff[512] = {0};
    char tod[32] = {0};
    char type[32] = {0};

    switch (lc) {
    case LOG:
        sprintf(type, "\x1B[1;32mKARTE LOG\x1B[0;37m");
        break;
    case ERROR:
        sprintf(type, "\x1B[1;31mKARTE ERR\x1B[0;37m");
        break;
    case WARNING:
        sprintf(type, "\x1B[1;33mKARTE WRN\x1B[0;37m");
        break;
    default:
        sprintf(type, "\x1B[1;32mKARTE LOG\x1B[0;37m");
        break;
    }

    TimeOfDay(tod);

    sprintf(buff, "[%s %s] %s\n", tod, type, str);

    va_list ap;
    va_start(ap, str);
    if (lc == ERROR) {
        vfprintf(stderr, buff, ap);
    } else {
        vfprintf(stdout, buff, ap);
    }
    va_end(ap);
}

/* -------------------------------------------------------------------------- */
/* MEMORY                                                                     */
/* -------------------------------------------------------------------------- */
static inline void *Allocate(const size_t size) {
    void *mem = calloc(1, size);
    if (mem == NULL) {
        return NULL;
    }

    ++g_mem_allocs;
    return mem;
}

static inline void Destroy(void *mem) {
    free(mem);
    --g_mem_allocs;
}

/* -------------------------------------------------------------------------- */
/* MISCELLANEOUS                                                              */
/* -------------------------------------------------------------------------- */
static inline void TimeOfDay(char *dest) {
    char buff[27] = {0};
    struct tm *tm_info = NULL;
    time_t timer = {0};
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buff, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    strcpy(dest, buff);
}

#endif