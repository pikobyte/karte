/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file texture.h
 *
 * \brief Textures hold a set of 16x16 glyphs that are used for most rendering.
 * The texture holds some data about the SDL_Texture it contains, such as glyph
 * width and height.
 *
 * \author Anthony Mercer
 *
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "definitions.h"
#include "utils.h"
#include "window.h"

/**
 * \brief Holds a pointer to an SDL_Texture as well as some metadata.
 *
 * The Texture object acts as a wrapper around a SDL_Texture, but with extra
 * data stored. These data contain the texture dimensions and the dimensions of
 * each glyph, assuming that each texture is a set of 16x16 glyphs. A set of 256
 * source rectangles are stored for quick look-up when required.
 */
typedef struct Texture_s {
    SDL_Texture *sdl_texture;
    u32 width;
    u32 height;
    u32 glyph_w;
    u32 glyph_h;
    SDL_Rect rects[256];
} Texture;

/**
 * \brief Allocates memory for the texture.
 * \returns A pointer to an texture object.
 */
Texture *TextureCreate(void);

/**
 * \brief Frees the texture memory.
 * \param [in, out] The texture to be freed.
 * \returns Void.
 */
void TextureFree(Texture *tex);

/**
 * \brief Loads an image file into a texture.
 * \param [in, out] tex The texture object the image should be loaded into.
 * \param [in] wind The window object holding the SDL_Renderer.
 * \param [in] path The path to the image file.
 * \returns Void.
 */
void TextureLoad(Texture *tex, const Window *wind, const char *path);

#endif