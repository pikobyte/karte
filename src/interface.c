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
Interface *InterfaceCreate(u32 sx, u32 sy) {
    Interface *itfc = Allocate(sizeof(Interface));
    Log(LOG_NOTIFY, "Created interface at %p.", itfc);
    itfc->sx = sx;
    itfc->sy = sy;

    itfc->cur_glyph = GlyphCreate();
    itfc->cur_glyph->x = 17 * sx;
    itfc->cur_glyph->y = 14 * sy;
    itfc->cur_glyph->fg = BLUE;
    itfc->cur_glyph->index = 1;
    itfc->show_ghost = false;

    // BUTTONS -----------------------------------------------------------------
    Button *b1 = ButtonCreate(sx, sy, 1, 41, "Quit", BORDER_SINGLE, GREY,
                              LIGHTGREY, true);
    Button *b2 = ButtonCreate(sx, sy, 7, 41, "Save", BORDER_SINGLE, GREY,
                              LIGHTGREY, false);
    Button *b3 = ButtonCreate(sx, sy, 13, 41, "Load", BORDER_SINGLE, GREY,
                              LIGHTGREY, false);
    ArrayPush(itfc->widgets,
              WidgetCreate("quit_button", WIDGET_BUTTON, b1, 0, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("save_button", WIDGET_BUTTON, b2, 0, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("load_button", WIDGET_BUTTON, b3, 0, 0));

    // CANVASES ----------------------------------------------------------------
    Canvas *c1 =
        CanvasCreate(sx, sy, (SDL_Rect){21, 1, 58, 43}, CANVAS_EDITOR, true);
    for (i8 i = 0; i < 58; ++i) {
        for (i8 j = 0; j < 43; ++j) {
            Glyph *glyph = GlyphCreate();
            glyph->x = (i * sx) + c1->rect.x;
            glyph->y = (j * sy) + c1->rect.y;
            glyph->fg = LIGHTGREY;
            glyph->index = 1;
            ArrayPush(c1->glyphs, glyph);
        }
    }

    Canvas *c2 =
        CanvasCreate(sx, sy, (SDL_Rect){2, 24, 17, 16}, CANVAS_GLYPH, false);
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

    Canvas *c3 =
        CanvasCreate(sx, sy, (SDL_Rect){2, 17, 16, 4}, CANVAS_COLOR, false);
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

    ArrayPush(itfc->widgets,
              WidgetCreate("canvas_main", WIDGET_CANVAS, c1, 0, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("canvas_glyphs", WIDGET_CANVAS, c2, 0, 0));
    ArrayPush(itfc->widgets,
              WidgetCreate("canvas_colors", WIDGET_CANVAS, c3, 0, 0));

    // LABELS ------------------------------------------------------------------
    Label *l1 = LabelCreate(sx, sy, 4, 0, "Karte v0.0.1", DARKGREY, LIGHTGREY);
    Label *l2 = LabelCreate(sx, sy, 2, 16, "Colours", LIGHTGREY, BLACK);
    Label *l3 = LabelCreate(sx, sy, 2, 23, "Glyphs", LIGHTGREY, BLACK);
    Label *l4 = LabelCreate(sx, sy, 2, 14, "Current glyph:", LIGHTGREY, BLACK);

    ArrayPush(itfc->widgets, WidgetCreate("title", WIDGET_LABEL, l1, 0, 1));
    ArrayPush(itfc->widgets,
              WidgetCreate("color_title", WIDGET_LABEL, l2, 0, 1));
    ArrayPush(itfc->widgets,
              WidgetCreate("glyph_title", WIDGET_LABEL, l3, 0, 1));
    ArrayPush(itfc->widgets,
              WidgetCreate("current_glyph", WIDGET_LABEL, l4, 0, 1));

    // PANELS ------------------------------------------------------------------
    Panel *p1 =
        PanelCreate(sx, sy, (SDL_Rect){0, 0, 20, 45}, BORDER_SINGLE, LIGHTGREY);
    Panel *p2 = PanelCreate(sx, sy, (SDL_Rect){20, 0, 60, 45}, BORDER_SINGLE,
                            LIGHTGREY);
    Panel *p3 =
        PanelCreate(sx, sy, (SDL_Rect){1, 16, 18, 6}, BORDER_SINGLE, LIGHTGREY);
    Panel *p4 = PanelCreate(sx, sy, (SDL_Rect){1, 23, 18, 18}, BORDER_SINGLE,
                            LIGHTGREY);

    ArrayPush(itfc->widgets, WidgetCreate("options", WIDGET_PANEL, p1, 0, 0));
    ArrayPush(itfc->widgets, WidgetCreate("editor", WIDGET_PANEL, p2, 0, 0));
    ArrayPush(itfc->widgets, WidgetCreate("color_box", WIDGET_PANEL, p3, 0, 0));
    ArrayPush(itfc->widgets, WidgetCreate("glyph_box", WIDGET_PANEL, p4, 0, 0));

    qsort(itfc->widgets, ArrayCount(itfc->widgets), sizeof(Widget *),
          &InterfaceSortByRenderOrder);

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
 * their corresponding data.
 */
void InterfaceHandleInput(Interface *itfc, Input *input) {
    for (i32 i = 0; i < ArrayCount(itfc->widgets); ++i) {
        WidgetHandleInput(itfc->widgets[i], input);
    }

    Button *quit_button =
        (Button *)InterfaceRetrieveWidget(itfc, "quit_button", WIDGET_BUTTON)
            ->data;
    if (ButtonIsPressed(quit_button)) {
        input->quit = true;
    }
}

/**
 * \desc Updates the UI widgets that need it. This is typically changes in
 * component state as well as visual appearance for user feedback. The current
 * paintable glyph is also set here based on the selected glyph in the options
 * panel.
 */
void InterfaceUpdate(Interface *itfc) {
    for (i32 i = 0; i < ArrayCount(itfc->widgets); ++i) {
        WidgetUpdate(itfc->widgets[i], itfc->cur_glyph);
    }

    SDL_Point mpos = InputMouseSnap(itfc->sx, itfc->sy);
    Canvas *main_canvas =
        (Canvas *)InterfaceRetrieveWidget(itfc, "canvas_main", WIDGET_CANVAS)
            ->data;
    itfc->show_ghost = SDL_PointInRect(&mpos, &main_canvas->rect);
}

/**
 * \desc Renders the whole interface by iterating through each widget. The
 * current glyph is also rendered as well as a ghost glyph if the flag is set.
 */
void InterfaceRender(const Interface *itfc, const Window *wind,
                     const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(itfc->widgets); ++i) {
        WidgetRender(itfc->widgets[i], wind, tex);
    }

    if (itfc->show_ghost) {
        itfc->cur_glyph->x = InputMouseSnapX(itfc->sx);
        itfc->cur_glyph->y = InputMouseSnapY(itfc->sy);
        GlyphRender(itfc->cur_glyph, wind, tex);
        itfc->cur_glyph->x = 17 * itfc->sx;
        itfc->cur_glyph->y = 14 * itfc->sy;
    }

    GlyphRender(itfc->cur_glyph, wind, tex);
}

/**
 * \desc A callback function for the sorting of widgets by their render order.
 * The sorting is ascending: higher render order widgets are rendered last.
 */
static i32 InterfaceSortByRenderOrder(const void *a, const void *b) {
    const Widget *x = *(const Widget **)a;
    const Widget *y = *(const Widget **)b;

    if (x->z < y->z) {
        return -1;
    } else if (x->z > y->z) {
        return 1;
    }

    return 0;
}

/**
 * \desc Retrieves a widget based on an identifier and a widget type. Only if
 * these two conform together is the widget returned. Otherwise, the return
 * value is NULL.
 */
static Widget *InterfaceRetrieveWidget(const Interface *itfc, const char *id,
                                       WidgetType type) {
    for (i32 i = 0; i < ArrayCount(itfc->widgets); ++i) {
        const char *cur_id = itfc->widgets[i]->id;
        const WidgetType cur_type = itfc->widgets[i]->type;
        if (!strcmp(id, cur_id) && type == cur_type) {
            return itfc->widgets[i];
        }
    }

    return NULL;
}