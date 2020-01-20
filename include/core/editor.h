/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file editor.h
 *
 * \brief The editor is where all of the functionality of the Karte program is
 * handled.
 *
 * \author Anthony Mercer
 *
 */

#ifndef EDITOR_H
#define EDITOR_H

#include "core/common.h"
#include "core/input.h"
#include "core/resourcer.h"
#include "core/utils.h"
#include "graphics/glyph.h"
#include "graphics/texture.h"
#include "graphics/window.h"
#include "memory/hashmap.h"
#include "memory/vector.h"
#include "ui/interface.h"

/**
 * \brief Stores data pertaining to the editor state.
 *
 * The editor is where most of the program input is processed and fed back to
 * the user. The editor contains a UI where the input from the user is taken and
 * fed back appropriately.
 */
typedef struct Editor_s {
    bool visible;    /**< Visible components flag. */
    Interface *itfc; /**< The user interface. */
    Texture *tex;    /**< Texture for the glyphs. */
} Editor;

/**
 * \brief Creates the editor object and initialises textures and glyphs.
 * \param [in] wind A window holding an SDL renderer so that a texture can be
 * created.
 * \returns Pointer to an application object.
 */
Editor *EditorCreate(const Window *wind, Resourcer *res);

/**
 * \brief Frees the editor memory.
 * \param [in, out] editor The editor to be freed.
 * \returns Void.
 */
void EditorFree(Editor *editor);

/**
 * \brief Deals with editor input.
 * \param [in, out] editor The editor to be freed.
 * \param [in] input The input handler to poll.
 * \returns Void.
 */
void EditorHandleInput(Editor *editor, Input *input);

/**
 * \brief Updates the editor components.
 * \param [in, out] editor The editor to be updated.
 * \returns Void.
 */
void EditorUpdate(Editor *editor);

/**
 * \brief Renders the editor components.
 * \param [in, out] editor The editor to be rendered.
 * \param [in, out] wind The window to render to.
 * \returns Void.
 */
void EditorRender(const Editor *editor, const Window *wind);

#endif