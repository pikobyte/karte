/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file widget.c
 *
 * \brief A generic type used to hold UI widget data. Other pertinent
 * information is also stored by a widget, such as type and rendering priority.
 *
 * \author Anthony Mercer
 *
 */

#include "widget.h"

/**
 * \desc Creates a widget, first by allocating its memory, and then by assigning
 * the identifier, widget type, its specific data (button, canvas etc.), as well
 * as its interactive tab and its render order.
 */
Widget *WidgetCreate(const char *id, WidgetType type, void *data, u32 tab,
                     i32 z) {
    Widget *widget = Allocate(sizeof(Widget));
    strcpy(widget->id, id);
    widget->type = type;
    widget->data = data;
    widget->tab = tab;
    widget->z = z;
    return widget;
}

/**
 * \desc Frees the widget memory by checking which data it contains and calling
 * the corresponding function. The widget pointer is freed last.
 */
void WidgetFree(Widget *widget) {
    switch (widget->type) {
    case WIDGET_BUTTON: {
        ButtonFree((Button *)widget->data);
        break;
    }
    case WIDGET_CANVAS: {
        CanvasFree((Canvas *)widget->data);
        break;
    }
    case WIDGET_LABEL: {
        LabelFree((Label *)widget->data);
        break;
    }
    case WIDGET_PANEL: {
        PanelFree((Panel *)widget->data);
        break;
    }
    default: { break; }
    }

    Free(widget);
}

/**
 * \desc Handles widget input if the type requires it. This is done based on the
 * type of the widget and calls the corresponding handle input function.
 */
void WidgetHandleInput(const Widget *widget, const Input *input) {
    switch (widget->type) {
    case WIDGET_BUTTON: {
        ButtonHandleInput((Button *)widget->data, input);
        break;
    }
    case WIDGET_CANVAS: {
        CanvasHandleInput((Canvas *)widget->data, input);
        break;
    }
    case WIDGET_LABEL:
    case WIDGET_PANEL:
    default: { break; }
    }
}

/**
 * \desc Updates a widget that requires it. This is done based on the type of
 * the widget and calls the corresponding update function. Additionally, a glyph
 * can be set here, typically when updating a canvas.
 */
void WidgetUpdate(Widget *widget, Glyph *glyph) {
    switch (widget->type) {
    case WIDGET_BUTTON: {
        ButtonUpdate((Button *)widget->data);
        break;
    }
    case WIDGET_CANVAS: {
        CanvasUpdate((Canvas *)widget->data, glyph);
        break;
    }
    case WIDGET_LABEL:
    case WIDGET_PANEL:
    default: { break; }
    }
}

/**
 * \desc Renders a widget that requires it. This is done based on the
 * type of the widget and calls the corresponding render function.
 */
void WidgetRender(const Widget *widget, const Window *wind,
                  const Texture *tex) {
    switch (widget->type) {
    case WIDGET_BUTTON: {
        ButtonRender((Button *)widget->data, wind, tex);
        break;
    }
    case WIDGET_CANVAS: {
        CanvasRender((Canvas *)widget->data, wind, tex);
        break;
    }
    case WIDGET_LABEL: {
        LabelRender((Label *)widget->data, wind, tex);
        break;
    }
    case WIDGET_PANEL: {
        PanelRender((Panel *)widget->data, wind, tex);
        break;
    }
    default: { break; }
    }
}

/**
 * \desc A callback function for the sorting of widgets by their render order.
 * The sorting is ascending: higher render order widgets are rendered last.
 */
i32 WidgetSort(const void *a, const void *b) {
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
 * \desc Retrieves a widget based on an identifier. If it is found, return it.
 * Otherwise, the return value is NULL.
 */
Widget *WidgetFind(Widget **widgets, const char *id) {
    for (i32 i = 0; i < ArrayCount(widgets); ++i) {
        const char *cur_id = widgets[i]->id;
        if (!strcmp(id, cur_id)) {
            return widgets[i];
        }
    }

    return NULL;
}