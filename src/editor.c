/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file editor.c
 *
 * \brief The editor is where all of the functionality of the Karte program is
 * handled.
 *
 * \author Anthony Mercer
 *
 */

#include "editor.h"

/**
 * \desc Allocates the memory for the editor via the creation of the texture and
 * the renderable glyphs.
 */
Editor *EditorCreate(const Window *wind) {
    Editor *editor = Allocate(sizeof(Editor));
    Log(LOG, "Created editor at %p.", editor);

    editor->tex = TextureCreate();
    TextureLoad(editor->tex, wind, "res/textures/curses_16x16.png");

    for (u32 i = 0; i < 256; ++i) {
        editor->glyphs[i] = GlyphCreate();
        editor->glyphs[i]->index = i;
        editor->glyphs[i]->x = (i % 16) * editor->tex->glyph_w;
        editor->glyphs[i]->y = (i / 16) * editor->tex->glyph_h;
        editor->glyphs[i]->bg = (SDL_Color){0, 0, 0, 255};
        editor->glyphs[i]->fg = (SDL_Color){255, 255, 255, 255};
    }

    editor->visible = true;

    return editor;
}

/**
 * \desc Frees the memory for an editor object, including texture and glyph
 * memory.
 */
void EditorFree(Editor *editor) {
    for (u32 i = 0; i < 256; ++i) {
        GlyphFree(editor->glyphs[i]);
    }
    TextureFree(editor->tex);
    Free(editor);
}

/**
 * \desc Handles the input pertaining to the editor. This requires an input
 * object to poll for events.
 */
void EditorHandleInput(Editor *editor, const Input *input) {
    if (InputKeyPressed(input, SDLK_v)) {
        editor->visible ^= 1;
    }
}

/**
 * \desc Updates of all of the pertinent editor components, such as tool
 * selection and visible glyphs.
 */
void EditorUpdate(Editor *editor) { UNUSED(editor); }

/**
 * \desc Renders of all of the pertinent editor components provided the visible
 * flag is true.
 */
void EditorRender(const Editor *editor, const Window *wind) {
    if (editor->visible) {
        for (u32 i = 0; i < 256; ++i) {
            GlyphRender(editor->glyphs[i], wind, editor->tex);
        }
    }
}