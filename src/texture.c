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

#include "texture.h"

/**
 * \desc Allocates the memory for the texture object and nothing more.
 */
Texture *TextureCreate(void) {
    Texture *tex = Allocate(sizeof(Texture));
    Log(LOG, "Created texture at %p.", tex);
    return tex;
}

/**
 * \desc Frees the memory for a texture object and nothing more.
 */
void TextureFree(Texture *tex) { Free(tex); }

/**
 * \desc Loading an image into a texture object requires an SDL_Renderer for
 * things like pixel format, hence why a window object must be passed in. A
 * preliminary check is made to see if the file exists. If it does, an
 * SDL_Surface is created and the magenta pixels in the image are turned
 * transparent via the setting of the colour key. The SDL_Texture is created
 * from the surface and all metadata are stored in the texture object. If the
 * texture dimensions are not a factor of 16, an error is issued. The created
 * surface is freed and alpha blending is enable for the texture. Finally, the
 * texture source rectangles are created for quick access later.
 */
bool TextureLoad(Texture *tex, const Window *wind, const char *path) {
    if (!FileExists(path)) {
        Log(ERROR, "No such texture %s", path);
        return false;
    }

    SDL_Surface *surf = IMG_Load(path);
    if (surf == NULL) {
        Log(ERROR, "Could not load SDL_Surface for texture %s", path);
        return false;
    }
    SDL_SetColorKey(surf, 1, SDL_MapRGB(surf->format, 255, 0, 255));

    tex->sdl_texture = SDL_CreateTextureFromSurface(wind->sdl_renderer, surf);
    if (tex->sdl_texture == NULL) {
        Log(ERROR, "Could not load SDL_Texture for texture %s", path);
        return false;
    }

    tex->width = surf->w;
    tex->height = surf->h;
    tex->glyph_w = tex->width / 16;
    tex->glyph_h = tex->height / 16;

    if (tex->width % 16 != 0 || tex->height % 16 != 0) {
        Log(ERROR, "Incorrect texture dimensions for %s", path);
        return false;
    }

    SDL_FreeSurface(surf);
    SDL_SetTextureBlendMode(tex->sdl_texture, SDL_BLENDMODE_BLEND);

    for (u32 i = 0; i < 256; ++i) {
        tex->rects[i] =
            (SDL_Rect){(i % 16) * tex->glyph_w, (i / 16) * tex->glyph_h,
                       tex->glyph_w, tex->glyph_h};
    }

    return true;
}