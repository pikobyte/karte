/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file definitions.c
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

#define UNUSED(x) (void)(x)

static u32 g_mem_allocs = 0;

#endif