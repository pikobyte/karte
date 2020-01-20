/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file canvas.h
 *
 * \brief A canvas allows the retrieval and/or editing of glyphs in a contained
 * area. It acts a a region for drawing via the use of a set of tools.
 *
 * \author Anthony Mercer
 *
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "core/common.h"
#include "core/input.h"
#include "core/utils.h"
#include "graphics/color.h"
#include "graphics/glyph.h"
#include "graphics/texture.h"
#include "graphics/window.h"
#include "memory/vector.h"

/**
 * \brief Describes a canvas operation.
 *
 * Canvas operations are determined by the input applied to them by the user.
 * This then governs how the canvas is updated. The operations include glyph
 * placing, glyph selection and glyph erasure.
 */
typedef enum CanvasOperation_e {
    CANVAS_NONE = 0,
    CANVAS_PLACE = 1,
    CANVAS_SELECT = 2,
    CANVAS_ERASE = 3
} CanvasOperation;

typedef struct Canvas_s {
    Glyph **glyphs;     /**< List of glyphs within the canvas. */
    CanvasOperation op; /**< Current canvas operation. */
    i32 glyph_index;    /**< Index of glyph to perform operation. */
    SDL_Rect rect;      /**< Canvas dimensions in pixel units. */
    i32 offset_x;       /**< Offset of the canvas in the x-direction. */
    i32 offset_y;       /**< Offset of the canvas in the y-direction. */
    bool writable;      /**< Determines whether the canvas can be edited. */
} Canvas;

/**
 * \brief Create a canvas with initial dimensions.
 * \param [in] rect The dimensions of the canvas in glyph units.
 * \param [in] writable Sets whether the canvas can be written to.
 * \returns Pointer to a canvas object.
 */
Canvas *CanvasCreate(SDL_Rect rect, bool writable);

/**
 * \brief Frees the canvas memory.
 * \param [in, out] canvas The canvas to be freed.
 * \returns Void.
 */
void CanvasFree(Canvas *canvas);

/**
 * \brief Deals with the input of a canvas based on its type.
 * \param [in, out] canvas The canvas to test input from.
 * \param [in] input An input handler.
 * \returns Void.
 */
void CanvasHandleInput(Canvas *canvas, const Input *input);

/**
 * \brief Updates a canvas.
 * \param [in, out] canvas The canvas to be updated.
 * \param [in, out] cur_glyph A current glyph to be changed based on operation.
 * \returns Void.
 */
void CanvasUpdate(Canvas *canvas, Glyph *cur_glyph);

/**
 * \brief Renders a canvas.
 * \param [in] canvas Canvas to render.
 * \param [in] wind Window to render to.
 * \param [in] tex Texture to render from.
 * \returns Void.
 */
void CanvasRender(const Canvas *canvas, const Window *wind, const Texture *tex);

#endif