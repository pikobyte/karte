/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file glyph.c
 *
 * \brief Glyphs represent single characters taken from a texture and can be
 * rendered to a window.
 *
 * \author Anthony Mercer
 *
 */

#include "glyph.h"

/**
 * \desc Allocates the memory for the glyph object and nothing more.
 */
Glyph *GlyphCreate(void) { return Allocate(sizeof(Glyph)); }

/**
 * \desc Frees the memory for a glyph object and nothing more.
 */
void GlyphFree(Glyph *glyph) { Free(glyph); }

/**
 * \desc Glyph rendering requires a window to render to and a base texture. The
 * foreground source rectangle from the texture is that based on the glyph
 * index. The background source rectangle is always the same: that of the filled
 * ASCII character. The destination rectangle is based on the glyph position, as
 * well as the textures glyph dimensions. The background is drawn first,
 * followed by the foreground. Alpha blending is enabled for both of these.
 */
void GlyphRender(const Glyph *glyph, const Window *wind, const Texture *tex) {
    SDL_Rect fsrc = tex->rects[glyph->index];
    SDL_Rect bsrc = tex->rects[FILLED];
    SDL_Rect dest = {0};
    dest.x = (u32)glyph->x;
    dest.y = (u32)glyph->y;
    dest.w = tex->glyph_w;
    dest.h = tex->glyph_h;

    SDL_SetTextureColorMod(tex->sdl_texture, glyph->bg.r, glyph->bg.g,
                           glyph->bg.b);
    SDL_SetTextureAlphaMod(tex->sdl_texture, glyph->bg.a);
    SDL_RenderCopy(wind->sdl_renderer, tex->sdl_texture, &bsrc, &dest);

    SDL_SetTextureColorMod(tex->sdl_texture, glyph->fg.r, glyph->fg.g,
                           glyph->fg.b);
    SDL_SetTextureAlphaMod(tex->sdl_texture, glyph->fg.a);
    SDL_RenderCopy(wind->sdl_renderer, tex->sdl_texture, &fsrc, &dest);
}