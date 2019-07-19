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
/* ARRAYS                                                                     */
/* -------------------------------------------------------------------------- */
/**
 * \desc Given an array, it is checked for validity, and if it is, is freed.
 */
#define ArrayFree(arr) (arr ? free(ArrayPtr(arr)), 0 : 0)

/**
 * \desc Pushes a value to an array. If the array needs to grow given this
 * single item push, it does so. Otherwise, the used element count is
 * incremented, and that index is set to the desired pointer.
 */
#define ArrayPush(arr, v) (ArrayQueryGrow(arr, 1), arr[ArrayUsed(arr)++] = v)

/**
 * \desc Returns the number of used elements in array if it is valid.
 */
#define ArrayCount(arr) (arr ? ArrayUsed(arr) : 0)

/**
 * \desc Returns the last used member within an array.
 */
#define ArrayLast(arr) (arr ? arr[ArrayUsed(arr) - 1] : 0)

/**
 * \desc Removes the first member of an array and shrinks the array to
 * compensate.
 */
#define ArrayPopFront(arr) (arr = ArrayShrink(arr, 0, sizeof(*arr)))

/**
 * \desc Removes the last member of an array and shrinks the array to
 * compensate.
 */
#define ArrayPopBack(arr) (arr = ArrayShrink(arr, ArrayLast(arr), sizeof(*arr)))

/**
 * \desc Returns the pointer to an array data. The header includes two 32-bit
 * integers, the first holding the array size, the second the number of used
 * elements.
 */
#define ArrayPtr(arr) ((i32 *)(arr)-2)

/**
 * \desc Returns the size of the array which is stored in the first part of the
 * array header.
 */
#define ArraySize(arr) ArrayPtr(arr)[0]

/**
 * \desc Returns the used members of an array which is stored in the second part
 * of the array header.
 */
#define ArrayUsed(arr) ArrayPtr(arr)[1]

/**
 * \desc Checks if the array size is zero or if the current used elements plus
 * the desired elements is larger than the array size.
 */
#define ArrayReqGrow(arr, n) (arr == 0 || ArrayUsed(arr) + n >= ArraySize(arr))

/**
 * \desc Queries the array to see if the requirement to grow is true. If it is,
 * then the size is increased.
 */
#define ArrayQueryGrow(arr, n) (ArrayReqGrow(arr, n) ? ArrayGrow(arr, n) : 0)

/**
 * \desc Sets an array size to that required to fit in required elements.
 */
#define ArrayGrow(arr, n) (arr = ArrayGrowBy(arr, n, sizeof(*arr)))

/**
 * \brief Grows an array by increasing its size.
 * \param [in] arr Array to increase the size of.
 * \param [in] n The number of elements to grow the array by.
 * \param [in] size The size of object which populates the array.
 * \returns The reallocated array, with a pointer to the data i.e. after the
 * header.
 */
void *ArrayGrowBy(const void *arr, const i32 n, const i32 size);

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
typedef enum LogCode_e { LOG, WARN, ERR, FATAL } LogCode;

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