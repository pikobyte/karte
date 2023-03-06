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

#include "core/common.h"
#include "core/utils.h"
#include "graphics/window.h"

/**
 * \brief Holds a pointer to an SDL_Texture as well as some metadata.
 *
 * The Texture object acts as a wrapper around a SDL_Texture, but with extra
 * data stored. These data contain the texture dimensions and the dimensions of
 * each glyph, assuming that each texture is a set of 16x16 glyphs. A set of 256
 * source rectangles are stored for quick look-up when required.
 */
typedef struct [[nodiscard]]
{
    SDL_Texture* sdl_texture; /**< The SDL texture handle. */
    u32 width;                /**< Width of the texture in pixels. */
    u32 height;               /**< Height of the texture in pixels. */
    u32 glyph_w;              /**< Glyph width (width / 16). */
    u32 glyph_h;              /**< Glyph height (height / 16). */
    SDL_Rect rects[256];      /**< Cached source rectangles for glyphs. */
} Texture;

/**
 * \brief Allocates memory for the texture.
 * \returns A pointer to an texture object.
 */
[[nodiscard]] Texture* TextureCreate(void);

/**
 * \brief Frees the texture memory.
 * \param [in, out] tex The texture to be freed.
 * \returns Void.
 */
void TextureFree(Texture* tex);

/**
 * \brief Loads an image file into a texture.
 * \param [in, out] tex The texture object the image should be loaded into.
 * \param [in] wind The window object holding the SDL_Renderer.
 * \param [in] path The path to the image file.
 * \returns Success of texture creation.
 */
[[nodiscard]] bool TextureLoad(Texture* tex, const Window* wind,
                               const char* path);

#endif