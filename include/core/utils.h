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

#include "core/common.h"

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
typedef enum LogCode_e {
    LOG_NOTIFY,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
} LogCode;

/**
 * \brief Logs a formatted string with based on a log code.
 * \param [in] lc The log code.
 * \param [in] str The formatted string to be logged.
 * \param [in] ... Extra parameters required for the formatted string.
 * \returns Void.
 */
void Log(LogCode lc, const char *str, ...);

/* -------------------------------------------------------------------------- */
/* MEMORY                                                                     */
/* -------------------------------------------------------------------------- */
/**
 * \brief Allocates memory based on a size, and increments number of
 * allocations.
 * \param [in] size Size of memory to be allocated.
 * \returns Pointer to the allocated memory.
 */
void *Allocate(size_t size);

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

/**
 * \brief Determines whether a bit is set at a masked position for a 32-bit
 * integer. \param [in] src The source value. \param [in] mask The mask of bits
 * to check against. \returns Whether that bit set is enabled.
 */
bool Mask32(i32 src, i32 mask);

/**
 * \brief Determines whether a bit is set at a masked position for a 32-bit
 * integer. \param [in] src The source value. \param [in] mask The mask of bits
 * to check against. \returns Whether that bit set is enabled.
 */
bool Mask64(i64 src, i64 mask);

/**
 * \brief Determines whether an input integer is a prime value or not.
 * \param [in] value An input unsigned integer.
 * \returns Whether the input value is prime or not.
 */
i32 IsPrime(u32 value);

/**
 * \brief Calculates the next prime number from the given input.
 * \param [in] value An input unsigned integer.
 * \returns The next prime number from the input.
 */
u32 NextPrime(u32 value);

/* -------------------------------------------------------------------------- */
/* STRING                                                                     */
/* -------------------------------------------------------------------------- */
/**
 * \brief Checks if a character is in a string.
 * \param [in] str The string to be searched.
 * \param [in] search The character to be searched for.
 * \returns Whether the character exists within the string.
 */
bool StringContains(const char *str, char search);

#endif