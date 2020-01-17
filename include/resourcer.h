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

#include "common.h"
#include "texture.h"
#include "utils.h"
#include "window.h"

/**
 * \brief Handles all resources (who would've guessed) to be used within the
 * program.
 *
 * The resourcer stores either an array or array of pointer to certain key
 * resources.
 */
typedef struct Resourcer_s {
    Texture **textures; /**< Textures used by the program. */
} Resourcer;

/**
 * \brief Allocates memory for the resourcer.
 * \returns A pointer to a resourcer object.
 */
Resourcer *ResourcerCreate(void);

/**
 * \brief Frees the resourcer memory.
 * \param [in, out] res The resourcer to be freed.
 * \returns Void.
 */
void ResourcerFree(Resourcer *res);

/**
 * \brief Loads a texture into memory.
 * \param [out] res The resourcer to load the texture into.
 * \param [in] wind The window with SDL surface to load to.
 * \param [in] path The filepath of the texture.
 * \returns The loaded texture.
 */
Texture *ResourcerLoadTexture(Resourcer *res, const Window *wind,
                              const char *path);

#endif