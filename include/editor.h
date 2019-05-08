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

#include "definitions.h"
#include "glyph.h"
#include "input.h"
#include "texture.h"
#include "utils.h"
#include "window.h"

/**
 * \brief Stores data pertaining to the editor state.
 *
 * The editor is where most of the program input is processed and fed back to
 * the user.
 * TODO: Details about UI, rendering, I/O when implemented.
 */
typedef struct Editor_s {
    bool visible;   /**< Visible components flag. */
    Glyph **glyphs; /**< Set of renderable glyphs. */
    Texture *tex;   /**< Texture for the glyphs. */
} Editor;

/**
 * \brief Creates the editor object and initialises textures and glyphs.
 * \params [in] wind A window holding an SDL renderer so that a texture can be
 * created.
 * \returns Pointer to an application object.
 */
Editor *EditorCreate(const Window *wind);

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
void EditorHandleInput(Editor *editor, const Input *input);

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