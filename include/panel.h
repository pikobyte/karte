/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file panel.h
 *
 * \brief A panel is a rectangle of glyphs with either a single or double lined
 * border.
 *
 * \author Anthony Mercer
 *
 */

#ifndef PANEL_H
#define PANEL_H

#include "color.h"
#include "common.h"
#include "glyph.h"
#include "texture.h"
#include "utils.h"
#include "window.h"

/**
 * \desc Border types. None does what it says on the tin, and is used as a
 * default for buttons. Single and double are the lines which decorate the
 * border.
 */
typedef enum Border_e {
    BORDER_NONE = 0,
    BORDER_SINGLE = 1,
    BORDER_DOUBLE = 2
} Border;

/**
 * \desc Single border ASCII indices: top-left, top-right, bottom-left,
 * bottom-right, horizontal, vertical.
 */
static const u8 SINGLE_BORDER[6] = {218, 191, 192, 217, 196, 179};

/**
 * \desc Double border ASCII indices: top-left, top-right, bottom-left,
 * bottom-right, horizontal, vertical.
 */
static const u8 DOUBLE_BORDER[6] = {201, 187, 200, 188, 205, 186};

/**
 * \brief A simple rectangle to be rendered in ASCII glyphs.
 *
 * A panel has a set of glyphs, dimensions, a border type and a border colour.
 * The inside of the rectangle remains unfilled, but the border is drawn (if
 * set).
 */
typedef struct Panel_s {
    Glyph **glyphs; /**< List of glyphs. */
    SDL_Rect rect;  /**< Bounding rectangle in glyph units. */
    Border border;  /**< Border type. */
    SDL_Color col;  /**< Border colour. */
} Panel;

/**
 * \brief Create a label at a given position with a given colour.
 * \param [in] rect The dimensions of the panel in glyph units.
 * \param [in] border The border type.
 * \param [in] col Colour of the border.
 * \returns Pointer to a panel object.
 */
Panel *PanelCreate(SDL_Rect rect, Border border, SDL_Color col);

/**
 * \brief Frees the panel memory.
 * \param [in, out] panel The panel to be freed.
 * \returns Void.
 */
void PanelFree(Panel *panel);

/**
 * \brief Renders a panel.
 * \param [in] panel Panel to render.
 * \param [in] wind Window to render to.
 * \param [in] tex Texture to render from.
 * \returns Void.
 */
void PanelRender(const Panel *panel, const Window *wind, const Texture *tex);

#endif