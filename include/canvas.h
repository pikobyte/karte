/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file canvas.h
 *
 * \brief A canvas allows the retrieval and/or editing of glyphs in a contained
 * area. It can acts a a region for drawing via the use of a set of tools, or as
 * a selection tool.
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

/**
 * \brief Describes the type of canvas.
 *
 * Canvases can either be read or written to based on their type, which also
 * influences input. Editor canvases are read and write where glyphs can be
 * placed, erased and selected. Selection canvases are read only and glyphs can
 * only be selected.
 */
typedef enum CanvasType_s {
    CANVAS_EDITOR = 0,
    CANVAS_COLOR = 1,
    CANVAS_GLYPH = 2
} CanvasType;

/**
 * \brief Describes a canvas operation.
 *
 * Canvas operations are determined by the input applied to them by the user.
 * This then governs how the canvas is updated. The operations include glyph
 * placing, glyph selection and glyph erasure.
 */
typedef enum CanvasOperation_s {
    CANVAS_NONE = 0,
    CANVAS_PLACE = 1,
    CANVAS_SELECT = 2,
    CANVAS_ERASE = 3
} CanvasOperation;

typedef struct Canvas_s {
    char id[256];       /**< Identifier. */
    u32 sx;             /**< Glyph width. */
    u32 sy;             /**< Glyph height. */
    Glyph **glyphs;     /**< List of glyphs within the canvas. */
    CanvasType type;    /**< Canvas type. */
    CanvasOperation op; /**< Current canvas operation. */
    i64 glyph_index;    /**< Index of glyph to perform operation. */
    SDL_Rect rect;      /**< Canvas dimensions in pixel units. */
    u32 offset_x;       /**< Offset of the canvas in the x-direction. */
    u32 offset_y;       /**< Offset of the canvas in the y-direction. */
    bool writable;      /**< Determines whether the canvas can be edited. */
} Canvas;

/**
 * \brief Create a canvas with initial glyph and physical dimensions.
 * \param [in] id Identifier for the canvas.
 * \param [in] sx The width of a glyph.
 * \param [in] sy The height of a glyph.
 * \param [in] rect The dimensions of the canvas in glyph units.
 * \param [in] type The type of canvas to be created.
 * \param [in] writable Sets whether the canvas can be written to.
 * \returns Pointer to a canvas object.
 */
Canvas *CanvasCreate(const char *id, const u32 sx, const u32 sy,
                     const SDL_Rect rect, const CanvasType type,
                     const bool writable);

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