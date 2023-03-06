/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file resourcer.h
 *
 * \brief Handles the loading and unloading of resources used within the
 * program.
 *
 * \author Anthony Mercer
 *
 */

#ifndef RESOURCER_H
#define RESOURCER_H

#include "core/common.h"
#include "core/utils.h"
#include "graphics/texture.h"
#include "graphics/window.h"
#include "memory/hashmap.h"

/**
 * \brief Handles all resources (who would've guessed) to be used within the
 * program.
 *
 * The resourcer stores vectors of different resources such as textures. Other
 * types of resource can be added if required.
 */
typedef struct [[nodiscard]]
{
    Hashmap* textures; /**< Textures used by the program. */
} Resourcer;

/**
 * \brief Allocates memory for the resourcer.
 * \returns A pointer to a resourcer object.
 */
[[nodiscard]] Resourcer* ResourcerCreate(void);

/**
 * \brief Frees the resourcer memory.
 * \param [in, out] res The resourcer to be freed.
 * \returns Void.
 */
void ResourcerFree(Resourcer* res);

/**
 * \brief Loads a texture into memory.
 * \param [out] res The resourcer to load the texture into.
 * \param [in] wind The window with SDL surface to load to.
 * \param [in] path The filepath of the texture.
 * \param [in] key An associated key for later look-up.
 * \returns Void.
 */
void ResourcerLoadTexture(Resourcer* res, const Window* wind, const char* path,
                          const char* key);

/**
 * \brief Retrieves a texture from the resourcer.
 * \param [in] res The resourcer to retrieve the texture from.
 * \param [in] key The name of the texture to retrieve.
 */
[[nodiscard]] Texture* ResourcerGetTexture(const Resourcer* res,
                                           const char* key);

#endif