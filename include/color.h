/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file SDL_color.h
 *
 * \brief Definition of colours for ease-of-use access.
 *
 * \author Anthony Mercer
 *
 */

#ifndef SDL_COLOR_H
#define SDL_COLOR_H

#include "common.h"

#define LIGHTGREY                                                              \
    (SDL_Color) { 200, 200, 200, 255 }
#define GREY                                                                   \
    (SDL_Color) { 130, 130, 130, 255 }
#define DARKGREY                                                               \
    (SDL_Color) { 80, 80, 80, 255 }
#define YELLOW                                                                 \
    (SDL_Color) { 253, 249, 0, 255 }
#define GOLD                                                                   \
    (SDL_Color) { 255, 203, 0, 255 }
#define ORANGE                                                                 \
    (SDL_Color) { 255, 161, 0, 255 }
#define PINK                                                                   \
    (SDL_Color) { 255, 109, 194, 255 }
#define RED                                                                    \
    (SDL_Color) { 230, 41, 55, 255 }
#define MAROON                                                                 \
    (SDL_Color) { 190, 33, 55, 255 }
#define GREEN                                                                  \
    (SDL_Color) { 0, 228, 48, 255 }
#define LIME                                                                   \
    (SDL_Color) { 0, 158, 47, 255 }
#define DARKGREEN                                                              \
    (SDL_Color) { 0, 117, 44, 255 }
#define SKYBLUE                                                                \
    (SDL_Color) { 102, 191, 255, 255 }
#define BLUE                                                                   \
    (SDL_Color) { 0, 121, 241, 255 }
#define DARKBLUE                                                               \
    (SDL_Color) { 0, 82, 172, 255 }
#define PURPLE                                                                 \
    (SDL_Color) { 200, 122, 255, 255 }
#define VIOLET                                                                 \
    (SDL_Color) { 135, 60, 190, 255 }
#define DARKPURPLE                                                             \
    (SDL_Color) { 112, 31, 126, 255 }
#define BEIGE                                                                  \
    (SDL_Color) { 211, 176, 131, 255 }
#define BROWN                                                                  \
    (SDL_Color) { 127, 106, 79, 255 }
#define DARKBROWN                                                              \
    (SDL_Color) { 76, 63, 47, 255 }
#define WHITE                                                                  \
    (SDL_Color) { 255, 255, 255, 255 }
#define BLACK                                                                  \
    (SDL_Color) { 0, 0, 0, 255 }
#define BLANK                                                                  \
    (SDL_Color) { 0, 0, 0, 0 }

// TODO: This is not at all robust. For example, custom palettes. Only for
// testing purposes.
static const SDL_Color COLORS[24] = {
    { 200, 200, 200, 255 },
    { 130, 130, 130, 255 },
    { 80, 80, 80, 255 },
    { 253, 249, 0, 255 },
    { 255, 203, 0, 255 },
    { 255, 161, 0, 255 },
    { 255, 109, 194, 255 },
    { 230, 41, 55, 255 },
    { 190, 33, 55, 255 },
    { 0, 228, 48, 255 },
    { 0, 158, 47, 255 },
    { 0, 117, 44, 255 },
    { 102, 191, 255, 255 },
    { 0, 121, 241, 255 },
    { 0, 82, 172, 255 },
    { 200, 122, 255, 255 },
    { 135, 60, 190, 255 },
    { 112, 31, 126, 255 },
    { 211, 176, 131, 255 },
    { 127, 106, 79, 255 },
    { 76, 63, 47, 255 },
    { 255, 255, 255, 255 },
    { 0, 0, 0, 255 },
    { 0, 0, 0, 0 }
};

#endif