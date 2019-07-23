/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file panel.c
 *
 * \brief A panel is a rectangle of glyphs with either a single or double lined
 * border.
 *
 * \author Anthony Mercer
 *
 */

#include "panel.h"

/**
 * \desc The memory for the panel is allocated first and its dimensions set. If
 * there is no border, then no glyphs have to be created. When glyphs are
 * created, only a border is considered. Glyph indices are set based on corners,
 * horizontal and vertical edges.
 */
Panel *PanelCreate(u32 sx, u32 sy, SDL_Rect rect, Border border,
                   SDL_Color col) {
    Panel *panel = Allocate(sizeof(Panel));
    panel->sx = sx;
    panel->sy = sy;
    panel->rect = rect;

    if (border == BORDER_NONE) {
        return panel;
    }

    for (i32 i = 0; i < rect.w; ++i) {
        for (i32 j = 0; j < rect.h; ++j) {
            u8 index = 255;
            if (i == 0 && j == 0) {
                index = 0;
            } else if (i == rect.w - 1 && j == 0) {
                index = 1;
            } else if (i == 0 && j == rect.h - 1) {
                index = 2;
            } else if (i == rect.w - 1 && j == rect.h - 1) {
                index = 3;
            } else if (j == 0 || j == rect.h - 1) {
                index = 4;
            } else if (i == 0 || i == rect.w - 1) {
                index = 5;
            } else {
                continue;
            }

            Glyph *glyph = GlyphCreate();
            glyph->x = (rect.x + i) * sx;
            glyph->y = (rect.y + j) * sy;
            glyph->fg = col;
            glyph->bg = BLANK;
            glyph->index = border == BORDER_SINGLE ? SINGLE_BORDER[index]
                                                   : DOUBLE_BORDER[index];

            ArrayPush(panel->glyphs, glyph);
        }
    }

    return panel;
}

/**
 * \desc Frees a panels's memory, first by freeing the graphical glyphs, then
 * the panel pointer itself.
 */
void PanelFree(Panel *panel) {
    for (i32 i = 0; i < ArrayCount(panel->glyphs); ++i) {
        GlyphFree(panel->glyphs[i]);
    }
    ArrayFree(panel->glyphs);
    Free(panel);
}

/**
 * \desc Renders a panel to a window based on a given texture by iterating
 * through its glyphs.
 */
void PanelRender(const Panel *panel, const Window *wind, const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(panel->glyphs); ++i) {
        GlyphRender(panel->glyphs[i], wind, tex);
    }
}

/**
 * \desc The panel bounding rectangle is given in glyph units, and as such, to
 * check pixel boundedness, must be converted to pixel units. The function
 * returns whether a point lies within this pixel unit bounding rectangle.
 */
bool PanelWithin(const Panel *panel, SDL_Point point) {
    SDL_Rect r = panel->rect;
    r.x *= panel->sx;
    r.y *= panel->sy;
    r.w *= panel->sx;
    r.h *= panel->sy;

    return SDL_PointInRect(&point, &r);
}