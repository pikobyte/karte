/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file label.h
 *
 * \brief Handles the creation and rendering of text labels.
 *
 * \author Anthony Mercer
 *
 */

#ifndef LABEL_H
#define LABEL_H

#include "core/common.h"
#include "core/utils.h"
#include "graphics/glyph.h"
#include "graphics/texture.h"
#include "graphics/window.h"
#include "memory/vector.h"

/**
 * \brief A simple text label formed from ASCII glyphs.
 *
 * A label has a position, text as well as foreground and background colours.
 * The label is single-lined: escape control sequences are rendered as the
 * corresponding graphical glyph.
 */
typedef struct [[nodiscard]]
{
    Vector* glyphs; /**< Set of glyphs for label text. */
    i32 x;          /**< x-position of the label. */
    i32 y;          /**< y-position of the label. */
    char text[128]; /**< Stored label text. */
    SDL_Color fg;   /**< Label foreground colour. */
    SDL_Color bg;   /**< Label background colour. */
} Label;

/**
 * \brief Create a label at a given position with a given colour.
 * \param [in] x The x-position of the label in glyph units.
 * \param [in] y The y-position of the label in glyph units.
 * \param [in] text The label text to display.
 * \param [in] fg Foreground colour of the text.
 * \param [in] bg Background colour of the text.
 * \returns Pointer to a label object.
 */
[[nodiscard]] Label* LabelCreate(i32 x, i32 y, const char* text, SDL_Color fg,
                                 SDL_Color bg);

/**
 * \brief Frees the label memory.
 * \param [in, out] label The label to be freed.
 * \returns Void.
 */
void LabelFree(Label* label);

/**
 * \brief Renders a label.
 * \param [in] label Label to render.
 * \param [in] wind Window to render to.
 * \param [in] tex Texture to render from.
 * \returns Void.
 */
void LabelRender(const Label* label, const Window* wind, const Texture* tex);

#endif