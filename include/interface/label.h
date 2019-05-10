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

#include "definitions.h"
#include "glyph.h"
#include "utils.h"

/**
 * \brief A simple text label formed from ASCII glyphs.
 *
 * A label has a string identifier, position, text as well as foreground and
 * background colours. The label is single-lined: escape control sequences are
 * rendered as the corresponding graphical glyph.
 */
typedef struct Label_s {
    char id[256];   /**< Identifier. */
    Glyph **glyphs; /**< Set of glyphs for label text. */
    i32 x;          /**< x-position of the label. */
    i32 y;          /**< y-position of the label. */
    char text[128]; /**< Stored label text. */
    SDL_Color fg;   /**< Label foreground colour. */
    SDL_Color bg;   /**< Label background colour. */
} Label;

/**
 * \brief Create a label at a given position with a given colour.
 * \params [in] id Identifier for the label.
 * \params [in] sx The width of a glyph.
 * \params [in] sy The height of a glyph.
 * \params [in] x The x-position of the label in glyph units.
 * \params [in] y The y-position of the label in glyph units.
 * \params [in] text The label text to display.
 * \params [in] fg Foreground colour of the text.
 * \params [in] bg Background colour of the text.
 * \returns Pointer to a label object.
 */
Label *LabelCreate(const char *id, const u32 sx, const u32 sy, const i32 x,
                   const i32 y, const char *text, const SDL_Color fg,
                   const SDL_Color bg);

/**
 * \brief Frees the label memory.
 * \param [in, out] label The label to be freed.
 * \returns Void.
 */
void LabelFree(Label *label);

#endif