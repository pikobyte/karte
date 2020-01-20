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
    res->textures = HashmapCreate(HASHMAP_INITIAL_BASE_SIZE, TextureFree);
    Log(LOG_NOTIFY, "Created resourcer at %p.", res);
    return res;
}

/**
 * \desc Frees all of the data concerned with the resourcer. Beware freeing
 * memory outside of the resourcer!
 */
void ResourcerFree(Resourcer *res) {
    HashmapFree(res->textures, true);
    Free(res);
}

/**
 * \desc Loads a texture into the resourcer texture hashmap. This requires a
 * Window with an SDL rendering context, and of course, a filepath to the
 * texture.
 */
void ResourcerLoadTexture(Resourcer *res, const Window *wind, const char *path,
                          const char *key) {
    Texture *tex = TextureCreate();
    if (!TextureLoad(tex, wind, path)) {
        return;
    }

    HashmapInsert(res->textures, key, tex);
}

/**
 * \desc Retrieves a texture from a resourcer via a hashmap look-up based on a
 * given key. If the texture is not found within the hashmap, an error is
 * logged.
 */
Texture *ResourcerGetTexture(const Resourcer *res, const char *key) {
    Texture *tex = HashmapSearch(res->textures, "main_texture");
    if (tex == NULL) {
        Log(LOG_ERROR, "Could not retrieve texture \"%s\" from resourcer!",
            key);
        return NULL;
    }

    return tex;
}