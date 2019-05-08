/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file glyph.h
 *
 * \brief Glyphs represent single characters taken from a texture and can be
 * rendered to a window.
 *
 * \author Anthony Mercer
 *
 */

#ifndef GLYPH_H
#define GLYPH_H

#include "definitions.h"
#include "texture.h"
#include "window.h"

/**
 * \desc Defines the solid colour ASCII character.
 */
#define FILLED 219

/**
 * \brief Holds data for an ASCII character.
 *
 * A glyph holds positional, colour and index data for the extended ASCII
 * character set. The index ranges from 0-255 and represents the ASCII
 * character. The glyph is rendered at a 2-dimensional position (x, y) with
 * custom background and foreground colours.
 */
typedef struct Glyph_s {
    i32 index;
    f64 x;
    f64 y;
    SDL_Color bg;
    SDL_Color fg;
} Glyph;

/**
 * \brief Allocates memory for the glyph.
 * \returns A pointer to an glyph object.
 */
Glyph *GlyphCreate(void);

/**
 * \brief Frees the glyph memory.
 * \param [in, out] The glyph to be freed.
 * \returns Void.
 */
void GlyphFree(Glyph *glyph);

/**
 * \brief Renders a glyph to a window based on a texture.
 * \param [in] glyph The glyph to be rendered.
 * \param [in] wind The window to render to.
 * \param [in] tex The texture to render from.
 * \returns Void.
 */
void GlyphRender(const Glyph *glyph, const Window *wind, const Texture *tex);

#endif