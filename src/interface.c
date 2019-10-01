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

#include "interface.h"

/**
 * \desc Begins by allocating memory for the interface and assigning glyph
 * dimensions. The interface array are then created after this and pushed into
 * the interface widget array. The widgets are sorted by render order at the end
 * of the function.
 * TODO: Load from a JSON file or something similar.
 */
Interface *InterfaceCreate(Texture *tex) {
    Interface *itfc = Allocate(sizeof(Interface));
    Log(LOG_NOTIFY, "Created interface at %p.", itfc);

    itfc->tex = tex;
    itfc->cur_glyph = GlyphCreate();
    itfc->cur_glyph->x = 17;
    itfc->cur_glyph->y = 14;
    itfc->cur_glyph->fg = BLUE;
    itfc->cur_glyph->index = 1;
    itfc->show_ghost = false;
    itfc->active_tab = 1;

    InterfaceCreateWidgets(itfc);

    qsort(itfc->widgets, ArrayCount(itfc->widgets), sizeof(Widget *),
          &WidgetSort);

    return itfc;
}

/**
 * \desc Frees the interface memory by iterating through the interface widgets,
 * freeing each, freeing each array and finally the interface pointer.
 */
void InterfaceFree(Interface *itfc) {
    for (i32 i = 0; i < ArrayCount(itfc->widgets); ++i) {
        WidgetFree(itfc->widgets[i]);
    }
    ArrayFree(itfc->widgets);

    GlyphFree(itfc->cur_glyph);
    Free(itfc);
}

/**
 * \desc Handles the input for interactable UI widgets. The interactions are
 * based on widget type. Individual widgets can be tested against by retrieving
 * their corresponding data. Only the persistent widgets or widgets in the
 * current tab have their input handled.
 */
void InterfaceHandleInput(Interface *itfc, Input *input) {
    for (i32 i = 0; i < ArrayCount(itfc->widgets); ++i) {
        const u32 tab = itfc->widgets[i]->tab;
        if (tab == 0 || tab == itfc->active_tab) {
            WidgetHandleInput(itfc->widgets[i], input);
        }
    }

    Widget *btn_quit = WidgetFind(itfc->widgets, "btn_quit");
    if (btn_quit) {
        if (ButtonIsPressed((Button *)btn_quit->data)) {
            input->quit = true;
        }
    }

    Widget *btn_tab1 = WidgetFind(itfc->widgets, "btn_tab1");
    if (btn_tab1) {
        if (ButtonIsPressed((Button *)btn_tab1->data)) {
            itfc->active_tab = 1;
        }
    }

    Widget *btn_tab2 = WidgetFind(itfc->widgets, "btn_tab2");
    if (btn_tab2) {
        if (ButtonIsPressed((Button *)btn_tab2->data)) {
            itfc->active_tab = 2;
        }
    }

    if (InputKeyPressed(input, SDLK_1)) {
        itfc->active_tab = 1;
    } else if (InputKeyPressed(input, SDLK_2)) {
        itfc->active_tab = 2;
    }
}

/**
 * \desc Updates the UI widgets that need it. This is typically changes in
 * component state as well as visual appearance for user feedback. Only the
 * persistent widgets or widgets in the current tab are updated. The current
 * paintable glyph is also set here based on the selected glyph in the options
 * panel.
 */
void InterfaceUpdate(Interface *itfc) {
    for (i32 i = 0; i < ArrayCount(itfc->widgets); ++i) {
        const u32 tab = itfc->widgets[i]->tab;
        if (tab == 0 || tab == itfc->active_tab) {
            WidgetUpdate(itfc->widgets[i], itfc->cur_glyph);
        }
    }

    Widget *cvs_editor = WidgetFind(itfc->widgets, CANVAS_MAIN);
    if (cvs_editor) {
        SDL_Point mpos = InputMouseSnap(itfc->tex->glyph_w, itfc->tex->glyph_h);
        Canvas *data = (Canvas *)cvs_editor->data;
        SDL_Rect r = data->rect;
        itfc->show_ghost = SDL_PointInRect(&mpos, &r);
    }
}

/**
 * \desc Renders the whole interface by iterating through each widget. Only the
 * persistent widgets or widgets in the current tab are rendered. The current
 * glyph is also rendered, as well as a ghost glyph if the flag is set.
 */
void InterfaceRender(const Interface *itfc, const Window *wind,
                     const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(itfc->widgets); ++i) {
        const u32 tab = itfc->widgets[i]->tab;
        if (tab == 0 || tab == itfc->active_tab) {
            WidgetRender(itfc->widgets[i], wind, tex);
        }
    }

    if (itfc->show_ghost) {
        itfc->cur_glyph->x = InputMouseSnapX(itfc->tex->glyph_w);
        itfc->cur_glyph->y = InputMouseSnapY(itfc->tex->glyph_h);
        GlyphRender(itfc->cur_glyph, wind, tex);
        itfc->cur_glyph->x = 17;
        itfc->cur_glyph->y = 14;
    }

    if (itfc->active_tab == 1) {
        GlyphRender(itfc->cur_glyph, wind, tex);
    }
}

/**
 * \desc A convenience function which creates a set of widgets for an interface
 * based on hard-coded values. Each widget type created is grouped logically.
 */
void InterfaceCreateWidgets(Interface *itfc) {
    // BUTTONS -----------------------------------------------------------------
    Button *btn_quit =
        ButtonCreate(1, 41, "Quit", BORDER_SINGLE, GREY, LIGHTGREY, true);
    Button *btn_save =
        ButtonCreate(7, 41, "Save", BORDER_SINGLE, GREY, LIGHTGREY, false);
    Button *btn_load =
        ButtonCreate(13, 41, "Load", BORDER_SINGLE, GREY, LIGHTGREY, false);
    Button *btn_tab1 =
        ButtonCreate(2, 3, "1", BORDER_NONE, LIGHTGREY, BLANK, true);
    Button *btn_tab2 =
        ButtonCreate(4, 3, "2", BORDER_NONE, LIGHTGREY, BLANK, true);

    ArrayPush(itfc->widgets,
              WidgetCreate("btn_quit", WIDGET_BUTTON, btn_quit, 1, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("btn_save", WIDGET_BUTTON, btn_save, 1, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("btn_load", WIDGET_BUTTON, btn_load, 1, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("btn_tab1", WIDGET_BUTTON, btn_tab1, 0, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("btn_tab2", WIDGET_BUTTON, btn_tab2, 0, 0));

    // CANVASES ----------------------------------------------------------------
    Canvas *cvs_main =
        CanvasCreate((SDL_Rect){21, 1, 58, 43}, CANVAS_EDITOR, true);
    for (i8 i = 0; i < 58; ++i) {
        for (i8 j = 0; j < 43; ++j) {
            Glyph *glyph = GlyphCreate();
            glyph->x = i + cvs_main->rect.x;
            glyph->y = j + cvs_main->rect.y;
            glyph->fg = LIGHTGREY;
            glyph->index = 1;
            ArrayPush(cvs_main->glyphs, glyph);
        }
    }

    Canvas *cvs_glyphs =
        CanvasCreate((SDL_Rect){2, 24, 17, 16}, CANVAS_GLYPH, false);
    for (i8 i = 0; i < 16; ++i) {
        for (i8 j = 0; j < 16; ++j) {
            Glyph *glyph = GlyphCreate();
            glyph->x = i + cvs_glyphs->rect.x;
            glyph->y = j + cvs_glyphs->rect.y;
            glyph->fg = LIGHTGREY;
            glyph->index = i + j * 16;
            ArrayPush(cvs_glyphs->glyphs, glyph);
        }
    }

    Canvas *cvs_colors =
        CanvasCreate((SDL_Rect){2, 17, 16, 4}, CANVAS_COLOR, false);
    for (i8 i = 0; i < 16; ++i) {
        for (i8 j = 0; j < 4; ++j) {
            Glyph *glyph = GlyphCreate();
            glyph->x = i + cvs_colors->rect.x;
            glyph->y = j + cvs_colors->rect.y;
            glyph->fg = RED;
            glyph->index = FILLED;
            ArrayPush(cvs_colors->glyphs, glyph);
        }
    }

    ArrayPush(itfc->widgets,
              WidgetCreate(CANVAS_MAIN, WIDGET_CANVAS, cvs_main, 0, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("cvs_glyphs ", WIDGET_CANVAS, cvs_glyphs, 1, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("cvs_colors", WIDGET_CANVAS, cvs_colors, 1, 0));

    // LABELS ------------------------------------------------------------------
    Label *lbl_title = LabelCreate(4, 0, "Karte v0.0.1", DARKGREY, LIGHTGREY);
    Label *lbl_color = LabelCreate(2, 16, "Colours", LIGHTGREY, BLACK);
    Label *lb_glyph = LabelCreate(2, 23, "Glyphs", LIGHTGREY, BLACK);
    Label *lbl_current = LabelCreate(2, 14, "CurrentGlyph:", LIGHTGREY, BLACK);
    Label *lbl_tab1 = LabelCreate(2, 2, "Main", LIGHTGREY, BLACK);
    Label *lbl_tab2 = LabelCreate(2, 2, "Tools", LIGHTGREY, BLACK);

    ArrayPush(itfc->widgets,
              WidgetCreate("lbl_title", WIDGET_LABEL, lbl_title, 0, 1));
    ArrayPush(itfc->widgets,
              WidgetCreate("lbl_color", WIDGET_LABEL, lbl_color, 1, 1));
    ArrayPush(itfc->widgets,
              WidgetCreate("lbl_glyph", WIDGET_LABEL, lb_glyph, 1, 1));
    ArrayPush(itfc->widgets,
              WidgetCreate("lbl_current", WIDGET_LABEL, lbl_current, 1, 1));
    ArrayPush(itfc->widgets,
              WidgetCreate("lbl_tab1", WIDGET_LABEL, lbl_tab1, 1, 1));
    ArrayPush(itfc->widgets,
              WidgetCreate("lbl_tab2", WIDGET_LABEL, lbl_tab2, 2, 1));

    // PANELS ------------------------------------------------------------------
    Panel *pnl_options =
        PanelCreate((SDL_Rect){0, 0, 20, 45}, BORDER_SINGLE, LIGHTGREY);
    Panel *pnl_editor =
        PanelCreate((SDL_Rect){20, 0, 60, 45}, BORDER_SINGLE, LIGHTGREY);
    Panel *pnl_color_box =
        PanelCreate((SDL_Rect){1, 16, 18, 6}, BORDER_SINGLE, LIGHTGREY);
    Panel *pnl_glyph_box =
        PanelCreate((SDL_Rect){1, 23, 18, 18}, BORDER_SINGLE, LIGHTGREY);
    Panel *pnl_tab =
        PanelCreate((SDL_Rect){1, 2, 18, 3}, BORDER_SINGLE, LIGHTGREY);

    ArrayPush(itfc->widgets,
              WidgetCreate("pnl_options", WIDGET_PANEL, pnl_options, 0, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("pnl_editor", WIDGET_PANEL, pnl_editor, 0, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("pnl_color_box", WIDGET_PANEL, pnl_color_box, 1, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("pnl_glyph_box", WIDGET_PANEL, pnl_glyph_box, 1, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("pnl_tab", WIDGET_PANEL, pnl_tab, 0, 0));
}