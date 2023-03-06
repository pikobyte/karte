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

#include "ui/interface.h"

/**
 * \desc Begins by allocating memory for the interface and assigning glyph
 * dimensions. The interface componentes are then created after this and pushed
 * into the widget vector. The widgets are sorted by render order at the end of
 * the function.
 * TODO: Load from a JSON file or something similar.
 */
Interface *InterfaceCreate(Texture *tex)
{
    Interface *itfc = Allocate(sizeof(Interface));

    itfc->tex = tex;

    itfc->cur_glyph = GlyphCreate();
    itfc->ghost = GlyphCreate();

    itfc->cur_glyph->x = 17;
    itfc->cur_glyph->y = 14;

    itfc->show_ghost = false;
    itfc->active_tab = 1;
    itfc->drawing_area = (SDL_Rect){21, 1, 58, 43};

    itfc->widgets = VectorCreate();
    InterfaceCreateWidgets(itfc);

    qsort(itfc->widgets->data, VectorLength(itfc->widgets), sizeof(Widget *),
          &WidgetSort);

    return itfc;
}

/**
 * \desc Frees the interface memory by iterating through the interface widgets,
 * freeing each, freeing each vector and finally the interface pointer.
 */
void InterfaceFree(Interface *itfc)
{
    for (size_t i = 0; i < VectorLength(itfc->widgets); ++i)
    {
        Widget *widget = VectorAt(itfc->widgets, i);
        WidgetFree(widget);
    }
    VectorFree(itfc->widgets);

    GlyphFree(itfc->cur_glyph);
    GlyphFree(itfc->ghost);
    Free(itfc);
}

/**
 * \desc Handles the input for interactable UI widgets. The interactions are
 * based on widget type. Individual widgets can be tested against by retrieving
 * their corresponding data. Only the persistent widgets or widgets in the
 * current tab have their input handled.
 */
void InterfaceHandleInput(Interface *itfc, Input *input)
{
    for (size_t i = 0; i < VectorLength(itfc->widgets); ++i)
    {
        const Widget *widget = VectorAt(itfc->widgets, i);
        const u32 tab = widget->tab;
        if (tab == 0 || tab == itfc->active_tab)
        {
            WidgetHandleInput(widget, input);
        }
    }

    Widget *btn_quit = WidgetFind(itfc->widgets, "btn_quit");
    if (btn_quit)
    {
        if (ButtonIsPressed((Button *)btn_quit->data))
        {
            input->quit = true;
        }
    }

    Widget *btn_tab1 = WidgetFind(itfc->widgets, "btn_tab1");
    if (btn_tab1)
    {
        if (ButtonIsPressed((Button *)btn_tab1->data))
        {
            itfc->active_tab = 1;
        }
    }

    Widget *btn_tab2 = WidgetFind(itfc->widgets, "btn_tab2");
    if (btn_tab2)
    {
        if (ButtonIsPressed((Button *)btn_tab2->data))
        {
            itfc->active_tab = 2;
        }
    }

    if (InputKeyPressed(input, SDLK_1))
    {
        itfc->active_tab = 1;
    }
    else if (InputKeyPressed(input, SDLK_2))
    {
        itfc->active_tab = 2;
    }

    itfc->show_ghost = InputMouseWithin(input, itfc->drawing_area);
    if (itfc->show_ghost)
    {
        const SDL_Point snap = InputMouseSnapToGlyph(input);
        itfc->ghost->index = itfc->cur_glyph->index;
        itfc->ghost->fg = itfc->cur_glyph->fg;
        itfc->ghost->bg = itfc->cur_glyph->bg;
        itfc->ghost->x = snap.x;
        itfc->ghost->y = snap.y;
    }
}

/**
 * \desc Updates the UI widgets that need it. This is typically changes in
 * component state as well as visual appearance for user feedback. Only the
 * persistent widgets or widgets in the current tab are updated. The current
 * paintable glyph is also set here based on the selected glyph in the options
 * panel.
 */
void InterfaceUpdate(Interface *itfc)
{
    for (size_t i = 0; i < VectorLength(itfc->widgets); ++i)
    {
        Widget *widget = VectorAt(itfc->widgets, i);
        const u32 tab = widget->tab;
        if (tab == 0 || tab == itfc->active_tab)
        {
            WidgetUpdate(widget, itfc->cur_glyph);
        }
    }
}

/**
 * \desc Renders the whole interface by iterating through each widget. Only the
 * persistent widgets or widgets in the current tab are rendered. The current
 * glyph is also rendered, as well as a ghost glyph if the flag is set.
 */
void InterfaceRender(const Interface *itfc, const Window *wind,
                     const Texture *tex)
{
    for (size_t i = 0; i < VectorLength(itfc->widgets); ++i)
    {
        const Widget *widget = VectorAt(itfc->widgets, i);
        const u32 tab = widget->tab;
        if (tab == 0 || tab == itfc->active_tab)
        {
            WidgetRender(widget, wind, tex);
        }
    }

    if (itfc->show_ghost)
    {
        GlyphRender(itfc->ghost, wind, tex);
    }

    if (itfc->active_tab == 1)
    {
        GlyphRender(itfc->cur_glyph, wind, tex);
    }
}

/**
 * \desc A convenience function which creates a set of widgets for an interface
 * based on hard-coded values. Each widget type created is grouped logically.
 */
void InterfaceCreateWidgets(Interface *itfc)
{
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

    VectorPush(itfc->widgets,
               WidgetCreate("btn_quit", WIDGET_BUTTON, btn_quit, 1, 0));
    VectorPush(itfc->widgets,
               WidgetCreate("btn_save", WIDGET_BUTTON, btn_save, 1, 0));
    VectorPush(itfc->widgets,
               WidgetCreate("btn_load", WIDGET_BUTTON, btn_load, 1, 0));
    VectorPush(itfc->widgets,
               WidgetCreate("btn_tab1", WIDGET_BUTTON, btn_tab1, 0, 0));
    VectorPush(itfc->widgets,
               WidgetCreate("btn_tab2", WIDGET_BUTTON, btn_tab2, 0, 0));

    // CANVASES ----------------------------------------------------------------
    Canvas *cvs_main = CanvasCreate((SDL_Rect){21, 1, 58, 43}, true);
    for (i32 i = 0; i < 58; ++i)
    {
        for (i32 j = 0; j < 43; ++j)
        {
            Glyph *glyph = GlyphCreate();
            glyph->x = i + cvs_main->rect.x;
            glyph->y = j + cvs_main->rect.y;
            glyph->fg = LIGHTGREY;
            glyph->bg = BLACK;
            glyph->index = 250;
            VectorPush(cvs_main->glyphs, glyph);
        }
    }

    VectorPush(itfc->widgets,
               WidgetCreate("cvs_main", WIDGET_CANVAS, cvs_main, 0, 0));

    // LABELS ------------------------------------------------------------------
    Label *lbl_title = LabelCreate(4, 0, "Karte v0.0.1", DARKGREY, LIGHTGREY);
    Label *lbl_color = LabelCreate(2, 16, "Colours", LIGHTGREY, BLACK);
    Label *lb_glyph = LabelCreate(2, 23, "Glyphs", LIGHTGREY, BLACK);
    Label *lbl_current = LabelCreate(2, 14, "Current glyph:", LIGHTGREY, BLACK);
    Label *lbl_tab1 = LabelCreate(2, 2, "Main", LIGHTGREY, BLACK);
    Label *lbl_tab2 = LabelCreate(2, 2, "Tools", LIGHTGREY, BLACK);

    VectorPush(itfc->widgets,
               WidgetCreate("lbl_title", WIDGET_LABEL, lbl_title, 0, 1));
    VectorPush(itfc->widgets,
               WidgetCreate("lbl_color", WIDGET_LABEL, lbl_color, 1, 1));
    VectorPush(itfc->widgets,
               WidgetCreate("lbl_glyph", WIDGET_LABEL, lb_glyph, 1, 1));
    VectorPush(itfc->widgets,
               WidgetCreate("lbl_current", WIDGET_LABEL, lbl_current, 1, 1));
    VectorPush(itfc->widgets,
               WidgetCreate("lbl_tab1", WIDGET_LABEL, lbl_tab1, 1, 1));
    VectorPush(itfc->widgets,
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

    VectorPush(itfc->widgets,
               WidgetCreate("pnl_options", WIDGET_PANEL, pnl_options, 0, 0));
    VectorPush(itfc->widgets,
               WidgetCreate("pnl_editor", WIDGET_PANEL, pnl_editor, 0, 0));
    VectorPush(itfc->widgets, WidgetCreate("pnl_color_box", WIDGET_PANEL,
                                           pnl_color_box, 1, 0));
    VectorPush(itfc->widgets, WidgetCreate("pnl_glyph_box", WIDGET_PANEL,
                                           pnl_glyph_box, 1, 0));
    VectorPush(itfc->widgets,
               WidgetCreate("pnl_tab", WIDGET_PANEL, pnl_tab, 0, 0));

    // SELECTORS ---------------------------------------------------------------
    Selector *sct_glyphs =
        SelectorCreate((SDL_Rect){2, 24, 17, 16}, SELECTOR_INDEX);
    for (i32 i = 0; i < 16; ++i)
    {
        for (i32 j = 0; j < 16; ++j)
        {
            Glyph *glyph = GlyphCreate();
            glyph->x = i + sct_glyphs->rect.x;
            glyph->y = j + sct_glyphs->rect.y;
            glyph->fg = LIGHTGREY;
            glyph->bg = BLACK;
            glyph->index = i + j * 16;
            VectorPush(sct_glyphs->glyphs, glyph);
        }
    }

    Selector *sct_colors = SelectorCreate(
        (SDL_Rect){2, 17, 16, 4}, SELECTOR_FOREGROUND | SELECTOR_BACKGROUND);
    i32 x = 0, y = 0;
    const i32 dx[4] = {0, 1, 0, 1};
    const i32 dy[4] = {0, 0, 1, 1};
    for (i32 i = 0; i < 16; ++i)
    {
        if (i > 0 && i % 8 == 0)
        {
            x = 0;
            y += 2;
        }

        for (i32 j = 0; j < 4; ++j)
        {
            Glyph *glyph = GlyphCreate();
            glyph->x = sct_colors->rect.x + x + dx[j];
            glyph->y = sct_colors->rect.y + y + dy[j];
            glyph->fg = COLORS[i];
            glyph->bg = COLORS[i];
            glyph->index = FILLED;
            VectorPush(sct_colors->glyphs, glyph);
        }

        x += 2;
    }

    VectorPush(itfc->widgets,
               WidgetCreate("sct_glyphs ", WIDGET_SELECTOR, sct_glyphs, 1, 0));
    VectorPush(itfc->widgets,
               WidgetCreate("sct_colors", WIDGET_SELECTOR, sct_colors, 1, 0));
}