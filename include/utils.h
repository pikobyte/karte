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
/* I/O                                                                        */
/* -------------------------------------------------------------------------- */
/**
 * \brief Checks for the existence of a file.
 * \param [in] path The path to the file.
 * returns Existence of the file.
 */
bool FileExists(const char *path);

/* -------------------------------------------------------------------------- */
/* LOGGING                                                                    */
/* -------------------------------------------------------------------------- */
/**
 * \brief Enumeration to describe log codes.
 *
 * The list of log codes and thier usages are: log for general information
 * output, warning, error, and fatal. The latter causes the program to exit.
 */
typedef enum LogCode_e { LOG, WARNING, ERROR, FATAL } LogCode;

/**
 * \brief Logs a formatted string with based on a log code.
 * \param [in] lc The log code.
 * \param [in] str The formatted string to be logged.
 * \param [in] ... Extra parameters required for the formatted string.
 * \returns Void.
 */
void Log(const LogCode lc, const char *str, ...);

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
 * \param [in, out] mem A pointer to the memory to be freed.
 * \returns Void.
 */
void Free(void *mem);

/* -------------------------------------------------------------------------- */
/* MISCELLANEOUS                                                              */
/* -------------------------------------------------------------------------- */
/**
 * \brief Gets the date and time then puts it into a character buffer.
 * \param [in, out] dest The destination buffer.
 * \returns Void.
 */
void DateAndTime(char *dest);

#endif