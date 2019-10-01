/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file canvas.c
 *
 * \brief A canvas allows the retrieval and/or editing of glyphs in a contained
 * area. It acts a a region for drawing via the use of a set of tools.
 *
 * \author Anthony Mercer
 *
 */

#include "canvas.h"

/**
 * \desc First allocates the memory for the canvas then sets its current
 * operation, glyph index an dimensions in glyph co-ordinates.
 */
Canvas *CanvasCreate(SDL_Rect rect, bool writable) {
    Canvas *canvas = Allocate(sizeof(Canvas));
    canvas->op = CANVAS_NONE;
    canvas->glyph_index = -1;
    canvas->rect = rect;
    canvas->writable = writable;

    return canvas;
}

/**
 * \desc Frees the canvas memory by freeing the glyphs including the current
 * glyph.
 */
void CanvasFree(Canvas *canvas) {
    for (i32 i = 0; i < ArrayCount(canvas->glyphs); ++i) {
        GlyphFree(canvas->glyphs[i]);
    }
    ArrayFree(canvas->glyphs);
    Free(canvas);
}

/**
 * \desc Firstly resets the current canvas operation. Then checks for user input
 * on an canvas where mouse input is snapped to the glyph dimensions. If the
 * mouse is within the canvas then input is registered. If the canvas is not
 * writable, then the left mouse button selects the current glyph. If the canvas
 * is writable, then the left mouse button places, the right erases and the
 * middle selects the hovered over glyph. The canvas operation and glyph index
 * are then used during the canvas update.
 */
void CanvasHandleInput(Canvas *canvas, const Input *input) {
    canvas->op = CANVAS_NONE;

    if (!InputMouseWithin(input, canvas->rect)) {
        return;
    }

    for (i32 i = 0; i < ArrayCount(canvas->glyphs); ++i) {
        Glyph *glyph = canvas->glyphs[i];
        SDL_Rect rect = {0};
        rect.x = (u32)glyph->x;
        rect.y = (u32)glyph->y;
        rect.w = 1;
        rect.h = 1;

        if (!InputMouseWithin(input, rect)) {
            continue;
        }

        if (!canvas->writable) {
            if (InputMouseDown(input, SDL_BUTTON_LEFT) ||
                InputMousePressed(input, SDL_BUTTON_LEFT)) {
                canvas->op = CANVAS_SELECT;
                canvas->glyph_index = i;
            }
            continue;
        }

        if (InputMouseDown(input, SDL_BUTTON_LEFT) ||
            InputMousePressed(input, SDL_BUTTON_LEFT)) {
            canvas->op = CANVAS_PLACE;
            canvas->glyph_index = i;
        } else if (InputMouseDown(input, SDL_BUTTON_RIGHT) ||
                   InputMousePressed(input, SDL_BUTTON_RIGHT)) {
            canvas->op = CANVAS_ERASE;
            canvas->glyph_index = i;
        } else if (InputMouseDown(input, SDL_BUTTON_MIDDLE) ||
                   InputMousePressed(input, SDL_BUTTON_MIDDLE)) {
            canvas->op = CANVAS_SELECT;
            canvas->glyph_index = i;
        }
    }
}

/**
 * \desc The canvas is updated only updated if a passed in glyph requires change
 * (i.e. not NULL) and if the current glyph index is valid. The current glyph
 * passed in is used based on the canvas operation: placing sets the a canvas
 * glyph to the current glyph; selection sets the current glyph to a canvas
 * glyph (based on canvas type); erasure just sets a canvas glyph to blank.
 */
void CanvasUpdate(Canvas *canvas, Glyph *cur_glyph) {
    i64 i = canvas->glyph_index;

    if (!cur_glyph || i < 0 || i > ArrayCount(canvas->glyphs)) {
        return;
    }

    switch (canvas->op) {
    case CANVAS_NONE: {
        break;
    }
    case CANVAS_PLACE: {
        canvas->glyphs[i]->fg = cur_glyph->fg;
        canvas->glyphs[i]->bg = cur_glyph->bg;
        canvas->glyphs[i]->index = cur_glyph->index;
        break;
    }
    case CANVAS_SELECT: {
        cur_glyph->fg = canvas->glyphs[i]->fg;
        cur_glyph->bg = canvas->glyphs[i]->bg;
        cur_glyph->index = canvas->glyphs[i]->index;
        break;
    }
    case CANVAS_ERASE: {
        canvas->glyphs[i]->index = 0;
        canvas->glyphs[i]->fg = BLANK;
        canvas->glyphs[i]->bg = BLANK;
        break;
    }
    default:
        break;
    }
}

/**
 * \desc Renders a canvas to a window based on a given texture by iterating
 * through its glyphs.
 */
void CanvasRender(const Canvas *canvas, const Window *wind,
                  const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(canvas->glyphs); ++i) {
        GlyphRender(canvas->glyphs[i], wind, tex);
    }
}