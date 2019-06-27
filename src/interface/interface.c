/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file interface.c
 *
 * \brief The user interface components and behaviour are stored and handled
 * here.
 *
 * \author Anthony Mercer
 *
 */

#include "interface/interface.h"

/**
 * \desc Begins by allocating memory for the interface and assigning glyph
 * dimensions. The interface components are then created after this and push
 * into the interface arrays.
 * TODO: Load from a JSON file or something similar.
 */
Interface *InterfaceCreate(const u32 sx, const u32 sy) {
    Interface *itfc = Allocate(sizeof(Interface));
    Log(LOG, "Created interface at %p.", itfc);
    itfc->sx = sx;
    itfc->sy = sy;

    itfc->cur_glyph = GlyphCreate();
    itfc->cur_glyph->x = 17 * sx;
    itfc->cur_glyph->y = 13 * sy;
    itfc->cur_glyph->fg = RED;
    itfc->cur_glyph->index = 1;
    itfc->show_ghost = false;

    Button *b1 = ButtonCreate("quit_button", sx, sy, 2, 40, "Quit", SINGLE,
                              GREY, LIGHTGREY, true);
    Button *b2 = ButtonCreate("save_button", sx, sy, 8, 40, "Save", SINGLE,
                              GREY, LIGHTGREY, false);
    Button *b3 = ButtonCreate("load_button", sx, sy, 14, 40, "Load", SINGLE,
                              GREY, LIGHTGREY, false);
    ArrayPush(itfc->buttons, b1);
    ArrayPush(itfc->buttons, b2);
    ArrayPush(itfc->buttons, b3);

    Canvas *c1 = CanvasCreate("canvas_main", sx, sy, (SDL_Rect){22, 2, 56, 41},
                              CANVAS_EDITOR, true);
    for (i8 i = 0; i < 56; ++i) {
        for (i8 j = 0; j < 41; ++j) {
            Glyph *glyph = GlyphCreate();
            glyph->x = (i * sx) + c1->rect.x;
            glyph->y = (j * sy) + c1->rect.y;
            glyph->fg = LIGHTGREY;
            glyph->index = 1;
            ArrayPush(c1->glyphs, glyph);
        }
    }
    ArrayPush(itfc->canvases, c1);

    Canvas *c2 = CanvasCreate("canvas_glyphs", sx, sy,
                              (SDL_Rect){3, 23, 16, 16}, CANVAS_GLYPH, false);
    for (i8 i = 0; i < 16; ++i) {
        for (i8 j = 0; j < 16; ++j) {
            Glyph *glyph = GlyphCreate();
            glyph->x = (i * sx) + c2->rect.x;
            glyph->y = (j * sy) + c2->rect.y;
            glyph->fg = LIGHTGREY;
            glyph->index = i + j * 16;
            ArrayPush(c2->glyphs, glyph);
        }
    }
    ArrayPush(itfc->canvases, c2);

    Canvas *c3 = CanvasCreate("canvas_colors", sx, sy, (SDL_Rect){3, 16, 16, 4},
                              CANVAS_COLOR, false);
    for (i8 i = 0; i < 16; ++i) {
        for (i8 j = 0; j < 4; ++j) {
            Glyph *glyph = GlyphCreate();
            glyph->x = (i * sx) + c3->rect.x;
            glyph->y = (j * sy) + c3->rect.y;
            glyph->fg = RED;
            glyph->index = FILLED;
            ArrayPush(c3->glyphs, glyph);
        }
    }
    ArrayPush(itfc->canvases, c3);

    Label *l1 =
        LabelCreate("title", sx, sy, 5, 1, "Karte v0.0.1", DARKGREY, LIGHTGREY);
    Label *l2 =
        LabelCreate("color_title", sx, sy, 4, 15, "Colours", LIGHTGREY, BLACK);
    Label *l3 =
        LabelCreate("glyph_title", sx, sy, 4, 22, "Glyphs", LIGHTGREY, BLACK);
    Label *l4 = LabelCreate("current_glyph", sx, sy, 2, 13,
                            "Current glyph:", LIGHTGREY, BLACK);
    ArrayPush(itfc->labels, l1);
    ArrayPush(itfc->labels, l2);
    ArrayPush(itfc->labels, l3);
    ArrayPush(itfc->labels, l4);

    Panel *p1 = PanelCreate("options", sx, sy, (SDL_Rect){1, 1, 20, 43}, SINGLE,
                            LIGHTGREY);
    Panel *p2 = PanelCreate("editor", sx, sy, (SDL_Rect){21, 1, 58, 43}, SINGLE,
                            LIGHTGREY);
    Panel *p3 = PanelCreate("color_box", sx, sy, (SDL_Rect){2, 15, 18, 6},
                            SINGLE, LIGHTGREY);
    Panel *p4 = PanelCreate("glyph_box", sx, sy, (SDL_Rect){2, 22, 18, 18},
                            SINGLE, LIGHTGREY);
    ArrayPush(itfc->panels, p1);
    ArrayPush(itfc->panels, p2);
    ArrayPush(itfc->panels, p3);
    ArrayPush(itfc->panels, p4);

    return itfc;
}

/**
 * \desc Frees the interface memory by iterating through the interface
 * components, freeing each, freeing each array and finally the interface
 * pointer.
 */
void InterfaceFree(Interface *itfc) {
    GlyphFree(itfc->cur_glyph);

    for (i32 i = 0; i < ArrayCount(itfc->buttons); ++i) {
        ButtonFree(itfc->buttons[i]);
    }
    ArrayFree(itfc->buttons);

    for (i32 i = 0; i < ArrayCount(itfc->canvases); ++i) {
        CanvasFree(itfc->canvases[i]);
    }
    ArrayFree(itfc->canvases);

    for (i32 i = 0; i < ArrayCount(itfc->labels); ++i) {
        LabelFree(itfc->labels[i]);
    }
    ArrayFree(itfc->labels);

    for (i32 i = 0; i < ArrayCount(itfc->panels); ++i) {
        PanelFree(itfc->panels[i]);
    }
    ArrayFree(itfc->panels);

    Free(itfc);
}

/**
 * \desc Handles the input for interactable UI components. The interactions are
 * based on component state and a provided component identifier which allows for
 * singular component behaviour.
 */
void InterfaceHandleInput(Interface *itfc, Input *input) {
    for (i32 i = 0; i < ArrayCount(itfc->buttons); ++i) {
        ButtonHandleInput(itfc->buttons[i], input);
        if (ButtonIsPressed(itfc->buttons[i], "quit_button")) {
            input->quit = true;
        }
    }

    for (i32 i = 0; i < ArrayCount(itfc->canvases); ++i) {
        CanvasHandleInput(itfc->canvases[i], input);
    }
}

/**
 * \desc Updates the UI components that need it. This is typically changes in
 * component state as well as visual appearance for user feedback. The current
 * paintable glyph is also set here based on the selected glyph in the options
 * panel.
 */
void InterfaceUpdate(Interface *itfc) {
    for (i32 i = 0; i < ArrayCount(itfc->buttons); ++i) {
        ButtonUpdate(itfc->buttons[i]);
    }

    for (i32 i = 0; i < ArrayCount(itfc->canvases); ++i) {
        CanvasUpdate(itfc->canvases[i], itfc->cur_glyph);
    }

    const SDL_Point mpos = InputMouseSnap(itfc->sx, itfc->sy);
    itfc->show_ghost = SDL_PointInRect(&mpos, &itfc->canvases[0]->rect);
}

/**
 * \desc Renders the whole interface by iterating through each component. The UI
 * buttons are rendered first, then canvases, followed by panels and finally
 * labels.
 * TODO: Update given different types of component.
 * TODO: Add z-layer for components and interleave.
 */
void InterfaceRender(const Interface *itfc, const Window *wind,
                     const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(itfc->buttons); ++i) {
        ButtonRender(itfc->buttons[i], wind, tex);
    }

    for (i32 i = 0; i < ArrayCount(itfc->canvases); ++i) {
        CanvasRender(itfc->canvases[i], wind, tex);
    }

    for (i32 i = 0; i < ArrayCount(itfc->panels); ++i) {
        PanelRender(itfc->panels[i], wind, tex);
    }

    for (i32 i = 0; i < ArrayCount(itfc->labels); ++i) {
        LabelRender(itfc->labels[i], wind, tex);
    }

    if (itfc->show_ghost) {
        itfc->cur_glyph->x = InputMouseSnapX(itfc->sx);
        itfc->cur_glyph->y = InputMouseSnapY(itfc->sy);
        GlyphRender(itfc->cur_glyph, wind, tex);
        itfc->cur_glyph->x = 17 * itfc->sx;
        itfc->cur_glyph->y = 13 * itfc->sy;
    }

    GlyphRender(itfc->cur_glyph, wind, tex);
}