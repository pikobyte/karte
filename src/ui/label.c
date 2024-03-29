/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file label.c
 *
 * \brief Handles the creation and rendering of text labels.
 *
 * \author Anthony Mercer
 *
 */

#include "ui/label.h"

/**
 * \desc Creates a label, first by allocating its memory, and then setting the
 * passed in parameters (for later use if required). The glyphs for the text are
 * created by looping through the string, and their positions are set based on
 * the input parameters as well as the glyph dimensions.
 */
[[nodiscard]] Label* LabelCreate(i32 x, i32 y, const char* text, SDL_Color fg,
                                 SDL_Color bg)
{
    Label* label = Allocate(sizeof(Label));
    label->glyphs = VectorCreate();
    label->x = x;
    label->y = y;
    strcpy(label->text, text);
    label->fg = fg;
    label->bg = bg;

    for (u32 i = 0; i < strlen(text); ++i)
    {
        Glyph* glyph = GlyphCreate();
        glyph->x = x + i;
        glyph->y = y;
        glyph->index = text[i];
        glyph->fg = fg;
        glyph->bg = bg;
        VectorPush(label->glyphs, glyph);
    }

    return label;
}

/**
 * \desc Frees a label's memory, first by freeing the graphical glyphs, then the
 * label pointer itself.
 */
void LabelFree(Label* label)
{
    for (size_t i = 0; i < VectorLength(label->glyphs); ++i)
    {
        Glyph* glyph = VectorAt(label->glyphs, i);
        GlyphFree(glyph);
    }

    VectorFree(label->glyphs);
    Free(label);
}

/**
 * \desc Renders a label to a window based on a given texture by iterating
 * through its glyphs.
 */
void LabelRender(const Label* label, const Window* wind, const Texture* tex)
{
    for (size_t i = 0; i < VectorLength(label->glyphs); ++i)
    {
        const Glyph* glyph = VectorAt(label->glyphs, i);
        GlyphRender(glyph, wind, tex);
    }
}