/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file canvas.c
 *
 * \brief A canvas allows the selection and, depending if possible, writing to a
 * glyph on the screen.
 *
 * \author Anthony Mercer
 *
 */

#include "interface/canvas.h"

/**
 * \desc First allocates the memory for the canvas then sets its ID and glyph
 * dimensions. The current glyph is then created and the canvas
 * dimensions are converted to pixel units.S
 */
Canvas *CanvasCreate(const char *id, const u32 sx, const u32 sy,
                     const SDL_Rect rect) {
    Canvas *canvas = Allocate(sizeof(Canvas));
    strcpy(canvas->id, id);
    canvas->sx = sx;
    canvas->sy = sy;

    // Fill canvas with random glyphs (temporary).
    for (i32 i = 0; i < rect.w; ++i) {
        for (i32 j = 0; j < rect.h; ++j) {
            Glyph *glyph = GlyphCreate();
            glyph->x = (rect.x + i) * sx;
            glyph->y = (rect.y + j) * sy;
            glyph->index = rand() % 255;
            glyph->fg = (SDL_Color){rand() % 255, rand() % 255, rand() % 255,
                                    rand() % 255};
            glyph->bg = (SDL_Color){rand() % 255, rand() % 255, rand() % 255,
                                    rand() % 255};
            ArrayPush(canvas->glyphs, glyph);
        }
    }

    canvas->show_ghost = false;
    canvas->cur_glyph = GlyphCreate();

    canvas->rect.x = rect.x * sx;
    canvas->rect.y = rect.y * sy;
    canvas->rect.w = rect.w * sx;
    canvas->rect.h = rect.h * sy;

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
    GlyphFree(canvas->cur_glyph);
    ArrayFree(canvas->glyphs);
    Free(canvas);
}

/**
 * \desc Checks for user input on an canvas where mouse input is snapped to the
 * glyph dimensions. If the mouse is within the canvas then input is registered.
 * The left mouse button paints, the right erases and the middle gets the
 * hovered over glyph.
 */
void CanvasHandleInput(Canvas *canvas, const Input *input) {
    const SDL_Point mpos = InputMouseSnap(canvas->sx, canvas->sy);
    for (i32 i = 0; i < ArrayCount(canvas->glyphs); ++i) {
        const Glyph *glyph = canvas->glyphs[i];
        const SDL_Rect r = {glyph->x, glyph->y, canvas->sx, canvas->sy};

        if (SDL_PointInRect(&mpos, &r)) {
            if (InputMouseDown(input, SDL_BUTTON_LEFT) ||
                InputMousePressed(input, SDL_BUTTON_LEFT)) {
                canvas->glyphs[i]->index = canvas->cur_glyph->index;
                canvas->glyphs[i]->fg = canvas->cur_glyph->fg;
                canvas->glyphs[i]->bg = canvas->cur_glyph->bg;
            } else if (InputMouseDown(input, SDL_BUTTON_RIGHT) ||
                       InputMousePressed(input, SDL_BUTTON_RIGHT)) {
                canvas->glyphs[i]->fg = BLANK;
                canvas->glyphs[i]->bg = BLANK;
                canvas->glyphs[i]->index = 0;
            } else if (InputMouseDown(input, SDL_BUTTON_MIDDLE) ||
                       InputMousePressed(input, SDL_BUTTON_MIDDLE)) {
                canvas->cur_glyph->index = canvas->glyphs[i]->index;
                canvas->cur_glyph->fg = canvas->glyphs[i]->fg;
                canvas->cur_glyph->bg = canvas->glyphs[i]->bg;
            }
        }
    }
}

/**
 * \desc Updates a canvas state by showing the current glyph whenever the mouse
 * is within the canvas boundary.
 */
void CanvasUpdate(Canvas *canvas) {
    const SDL_Point mpos = InputMouseSnap(canvas->sx, canvas->sy);
    if (SDL_PointInRect(&mpos, &canvas->rect)) {
        canvas->cur_glyph->x = mpos.x;
        canvas->cur_glyph->y = mpos.y;
        canvas->show_ghost = true;
    } else {
        canvas->show_ghost = false;
    }
}

/**
 * \desc Renders a canvas to a window based on a given texture by iterating
 * through its glyphs. The current glyph is shown above the canvas surface and
 * is therefore rendered afterward.
 */
void CanvasRender(const Canvas *canvas, const Window *wind,
                  const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(canvas->glyphs); ++i) {
        GlyphRender(canvas->glyphs[i], wind, tex);
    }

    if (canvas->show_ghost) {
        GlyphRender(canvas->cur_glyph, wind, tex);
    }
}