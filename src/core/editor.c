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

#include "core/editor.h"

/**
 * \desc Allocates the memory for the editor via the creation of the texture and
 * the renderable glyphs.
 */
[[nodiscard]] Editor* EditorCreate(const Window* wind, Resourcer* res)
{
    Editor* editor = Allocate(sizeof(Editor));

    ResourcerLoadTexture(res, wind, "./res/textures/boxy_16x16.png",
                         "main_texture");

    editor->tex = ResourcerGetTexture(res, "main_texture");
    editor->itfc = InterfaceCreate(editor->tex);
    editor->visible = true;

    return editor;
}

/**
 * \desc Frees the memory for an editor object, including texture and glyph
 * memory.
 */
void EditorFree(Editor* editor)
{
    InterfaceFree(editor->itfc);
    Free(editor);
}

/**
 * \desc Handles the input pertaining to the editor. This requires an input
 * object to poll for events.
 */
void EditorHandleInput(Editor* editor, Input* input)
{
    if (InputKeyPressed(input, SDLK_v))
    {
        editor->visible ^= 1;
    }

    InterfaceHandleInput(editor->itfc, input);
}

/**
 * \desc Updates of all of the pertinent editor components, such as tool
 * selection and visible glyphs.
 */
void EditorUpdate(Editor* editor) { InterfaceUpdate(editor->itfc); }

/**
 * \desc Renders of all of the pertinent editor components provided the visible
 * flag is true.
 */
void EditorRender(const Editor* editor, const Window* wind)
{
    if (editor->visible)
    {
        InterfaceRender(editor->itfc, wind, editor->tex);
    }
}