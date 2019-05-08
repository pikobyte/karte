/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file definitions.h
 *
 * \brief Definitions of types, structs, macros, constants and global variables
 * for the Karte program. This is where all common standard and external library
 * includes are stated.
 *
 * \author Anthony Mercer
 *
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

/**
 * \desc This is a utility macro which simply prevents the GCC unused-parameter
 * warning from firing. This should be removed in final releases.
 */
#define UNUSED(x) (void)(x)

/**
 * \desc Current working directory for the project. Requires changing for
 * release.
 */
static const char CWD[] = "/Documents/pikobyte/karte/";

/**
 * \desc The number of memory allocations that have been made during program
 * executions. Provided fatal issues do not occur, the number of allocations are
 * reported at the end of program execution for debugging purposes.
 */
u32 g_mem_allocs;

/**
 * \desc Absolute path to the application directory.
 */
char g_dir[1024];

#endif