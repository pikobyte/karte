/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file resourcer.c
 *
 * \brief Handles the loading and unloading of resources used within the
 * program.
 *
 * \author Anthony Mercer
 *
 */

#include "core/resourcer.h"

/**
 * \desc Allocates the memory for the resourcer object and nothing more.
 */
Resourcer *ResourcerCreate(void) {
    Resourcer *res = Allocate(sizeof(Resourcer));
    Log(LOG_NOTIFY, "Created resourcer at %p.", res);
    return res;
}

/**
 * \desc Frees all of the data concerned with the resourcer. Beware freeing
 * memory outside of the resourcer!
 */
void ResourcerFree(Resourcer *res) {
    for (i32 i = 0; i < VectorCount(res->textures); ++i) {
        TextureFree(res->textures[i]);
    }
    VectorFree(res->textures);
    Free(res);
}

/**
 * \desc Loads a texture into the resourcer texture vector. This requires a
 * Window with an SDL rendering context, and of course, a filepath to the
 * texture.
 */
Texture *ResourcerLoadTexture(Resourcer *res, const Window *wind,
                              const char *path) {
    Texture *tex = TextureCreate();
    if (!TextureLoad(tex, wind, path)) {
        return NULL;
    }

    VectorPush(res->textures, tex);
    return tex;
}