/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file utils.h
 * 
 * \brief General utility functions, from logging to memory and string
 * manipulation.
 *
 * \author Anthony Mercer
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include "definitions.h"

/* -------------------------------------------------------------------------- */
/* LOGGING                                                                    */
/* -------------------------------------------------------------------------- */
/**
 * \desc Enumeration to describe log codes.
 */
enum LogCode { LOG, ERROR, WARNING };

/**
 * \brief Logs a formatted string with based on a log code.
 * \param [in] lc The log code.
 * \param [in] str The formatted string to be logged.
 * \param [in] ... Extra parameters required for the formatted string.
 * \returns None.
 */
void Log(const enum LogCode lc, const char *str, ...);

/* -------------------------------------------------------------------------- */
/* MEMORY                                                                     */
/* -------------------------------------------------------------------------- */
/**
 * \brief Allocates memory based on a size, and increments number of
 * allocations.
 * \param [in] size Size of memory to be allocated.
 * \returns Pointer to the allocated memory.
 */
void *Allocate(const size_t size);

/**
 * \brief Deallocates memory and decrements the number of allocations.
 * \param [in] mem A pointer to the memory to be freed.
 * \returns None.
 */
void Destroy(void *mem);

/* -------------------------------------------------------------------------- */
/* MISCELLANEOUS                                                              */
/* -------------------------------------------------------------------------- */
/**
 * \brief Gets the date and time then puts it into a character buffer.
 * \param [in] dest The destination buffer.
 * \returns None.
 */
void DateAndTime(char *dest);

#endif