/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file canvas.h
 *
 * \brief A canvas allows the editing of glyphs in a contained area. It
 * essentially acts as a region for drawing via the use of a set of tools.
 *
 * \author Anthony Mercer
 *
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "color.h"
#include "definitions.h"
#include "glyph.h"
#include "input.h"
#include "texture.h"
#include "utils.h"
#include "window.h"

typedef struct Canvas_s {
    char id[256];     /**< Identifier. */
    u32 sx;           /**< Glyph width. */
    u32 sy;           /**< Glyph height. */
    Glyph **glyphs;   /**< List of glyphs within the canvas. */
    Glyph *cur_glyph; /**< Currently selected glyph. */
    SDL_Rect rect;    /**< Canvas dimensions in pixel units. */
    u32 offset_x;     /**< Offset of the canvas in the x-direction. */
    u32 offset_y;     /**< Offset of the canvas in the y-direction. */
    bool show_ghost;  /**< Flag to show current glyph. */
} Canvas;

/**
 * \brief Create a canvas with initial glyph and physical dimensions.
 * \param [in] id Identifier for the canvas.
 * \param [in] sx The width of a glyph.
 * \param [in] sy The height of a glyph.
 * \param [in] rect The dimensions of the canvas in glyph units.
 * \returns Pointer to a canvas object.
 */
Canvas *CanvasCreate(const char *id, const u32 sx, const u32 sy,
                     const SDL_Rect rect);

/**
 * \brief Frees the canvas memory.
 * \param [in, out] canvas The canvas to be freed.
 * \returns Void.
 */
void CanvasFree(Canvas *canvas);

/**
 * \brief Deals with the input of a canvas.
 * \param [in, out] canvas The canvas to test input from.
 * \param [in] input An input handler.
 * \returns Void.
 */
void CanvasHandleInput(Canvas *canvas, const Input *input);

/**
 * \brief Updates the canvas by setting the render current glyph flag based on
 * mouse position.
 * \param [in, out] canvas The canvas to be updated.
 * \returns Void.
 */
void CanvasUpdate(Canvas *canvas);

/**
 * \brief Renders a canvas.
 * \param [in] canvas Canvas to render.
 * \param [in] wind Window to render to.
 * \param [in] tex Texture to render from.
 * \returns Void.
 */
void CanvasRender(const Canvas *canvas, const Window *wind, const Texture *tex);

#endif