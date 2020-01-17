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
    selector->cur_glyph = GlyphCreate();
    selector->cur_glyph->index = 250;
    selector->cur_glyph->fg = LIGHTGREY;
    selector->cur_glyph->bg = BLACK;
    selector->type = type;
    selector->rect = rect;

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
    GlyphFree(selector->cur_glyph);
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

        if (InputMouseDown(input, SDL_BUTTON_LEFT)) {
            SelectorSetCurrentGlyph(selector, glyph,
                                    SELECTOR_INDEX | SELECTOR_FOREGROUND);
            return;
        }

        if (InputMouseDown(input, SDL_BUTTON_RIGHT)) {
            SelectorSetCurrentGlyph(selector, glyph, SELECTOR_BACKGROUND);
            return;
        }

        if (InputMouseDown(input, SDL_BUTTON_MIDDLE)) {
            SelectorSetCurrentGlyph(selector, glyph,
                                    SELECTOR_INDEX | SELECTOR_FOREGROUND |
                                        SELECTOR_BACKGROUND);
            return;
        }
    }
}

/**
 * \desc The data to confer over to the current interface glyph is based on the
 * flags set for a given selector. Glyph index, background colour and foreground
 * colour are set based on the flags.
 */
void SelectorUpdate(Selector *selector, Glyph *cur_glyph) {
    if (!cur_glyph) {
        return;
    }

    SelectorGetCurrentGlyph(selector, cur_glyph);
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

/**
 * \desc Sets the current glyph properties of a selector to those of a passed in
 * glyph. The properties are set subject to a selector type. For each type (of
 * which can be combined), the corresponding selector glyph properties are set.
 */
void SelectorSetCurrentGlyph(Selector *selector, const Glyph *glyph,
                             SelectorType type) {
    if (!glyph) {
        return;
    }

    if (Mask32(type, SELECTOR_INDEX)) {
        selector->cur_glyph->index = glyph->index;
    }

    if (Mask32(type, SELECTOR_FOREGROUND)) {
        selector->cur_glyph->fg = glyph->fg;
    }

    if (Mask32(type, SELECTOR_BACKGROUND)) {
        selector->cur_glyph->bg = glyph->bg;
    }
}

/**
 * \desc Sets the properties of a passed in glyph to those of a selector's
 * current glyph. The properties are set subject to the type of the passed in
 * selector. For each type (of which can be combined), the corresponding
 * selector glyph properties are set.
 */
void SelectorGetCurrentGlyph(const Selector *selector, Glyph *glyph) {
    if (!glyph) {
        return;
    }
    
    if (Mask32(selector->type, SELECTOR_INDEX)) {
        glyph->index = selector->cur_glyph->index;
    }

    if (Mask32(selector->type, SELECTOR_FOREGROUND)) {
        glyph->fg = selector->cur_glyph->fg;
    }

    if (Mask32(selector->type, SELECTOR_BACKGROUND)) {
        glyph->bg = selector->cur_glyph->bg;
    }
}