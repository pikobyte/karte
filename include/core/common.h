/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file common.h
 *
 * \brief Common definitions of types, structs, macros, constants and global
 * variables for the Karte program. This is where all common standard and
 * external library includes are stated.
 *
 * \author Anthony Mercer
 *
 */

#ifndef COMMON_H
#define COMMON_H

#if _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <io.h>
#include <windows.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#endif

#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
 * \desc The default conversion sizes from glyph co-ordinates to pixel
 * co-ordinates.
 */
static const SDL_Point DEFAULT_CONVERSION = {16, 16};

/**
 * \desc The number of memory allocations that have been made during program
 * executions. Provided fatal issues do not occur, the number of allocations are
 * reported at the end of program execution for debugging purposes.
 */
extern u32 g_mem_allocs;

#endif