/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file selector.h
 *
 * \brief A selector is a widget which allwos the user to choose a glyph or a
 * colour. The glyphs as part of the selector are immutable, in contrast to a
 * canvas.
 *
 * \author Anthony Mercer
 *
 */

#include "selector.h"

/**
 * \desc First allocates the memory for the selector then sets its type and
 * dimensions in glyph co-ordinates.
 */
Selector *SelectorCreate(SDL_Rect rect, SelectorType type) {
    Selector *selector = Allocate(sizeof(Selector));
    selector->type = type;
    selector->rect = rect;
    selector->cur_index = 1;

    return selector;
}

/**
 * \desc Frees the selector memory by freeing the glyphs including the current
 * glyph.
 */
void SelectorFree(Selector *selector) {
    for (i32 i = 0; i < ArrayCount(selector->glyphs); ++i) {
        GlyphFree(selector->glyphs[i]);
    }
    ArrayFree(selector->glyphs);
    Free(selector);
}

/**
 * \desc Iterates over the glyphs within a selector and checks whether the mouse
 * is within one of them. Given that it is, then mouse input is queried and if
 * successful, the current index is set based on the clicked glyph.
 */
void SelectorHandleInput(Selector *selector, const Input *input) {
    if (!InputMouseWithin(input, selector->rect)) {
        return;
    }

    for (i32 i = 0; i < ArrayCount(selector->glyphs); ++i) {
        Glyph *glyph = selector->glyphs[i];
        SDL_Rect rect = {0};
        rect.x = (u32)glyph->x;
        rect.y = (u32)glyph->y;
        rect.w = 1;
        rect.h = 1;

        if (!InputMouseWithin(input, rect)) {
            continue;
        }

        if (InputMousePressed(input, SDL_BUTTON_LEFT) ||
            InputMouseDown(input, SDL_BUTTON_LEFT)) {
            selector->cur_index = i;
        }
    }
}

/**
 * \desc The data to confer over to the current interface glyph is based on the
 * flags set for a given selector. Glyph index, background colour and foreground
 * colour are set based on the flags.
 */
void SelectorUpdate(Selector *selector, Glyph *cur_glyph) {
    i64 i = selector->cur_index;

    if (!cur_glyph || i < 0 || i > ArrayCount(selector->glyphs)) {
        return;
    }

    if (Mask32(selector->type, SELECTOR_INDEX)) {
        cur_glyph->index = selector->glyphs[i]->index;
    }

    if (Mask32(selector->type, SELECTOR_FOREGROUND)) {
        cur_glyph->fg = selector->glyphs[i]->fg;
    }

    if (Mask32(selector->type, SELECTOR_BACKGROUND)) {
        cur_glyph->bg = selector->glyphs[i]->bg;
    }
}

/**
 * \desc Renders a selector to a window based on a given texture by iterating
 * through its glyphs.
 */
void SelectorRender(const Selector *selector, const Window *wind,
                    const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(selector->glyphs); ++i) {
        GlyphRender(selector->glyphs[i], wind, tex);
    }
}