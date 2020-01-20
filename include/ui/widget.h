/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file widget.h
 *
 * \brief A generic type used to hold UI widget data. Other pertinent
 * information is also stored by a widget, such as type and rendering priority.
 *
 * \author Anthony Mercer
 *
 */

#ifndef WIDGET_H
#define WIDGET_H

#include "core/common.h"
#include "core/input.h"
#include "core/utils.h"
#include "graphics/color.h"
#include "graphics/glyph.h"
#include "memory/vector.h"
#include "ui/button.h"
#include "ui/canvas.h"
#include "ui/label.h"
#include "ui/panel.h"
#include "ui/selector.h"

typedef enum WidgetType_e {
    WIDGET_BUTTON,
    WIDGET_CANVAS,
    WIDGET_LABEL,
    WIDGET_PANEL,
    WIDGET_SELECTOR,
} WidgetType;

/**
 * \brief A widget is a generic UI component. They have identifiers, types (e.g.
 * buttons or labels), a pointer to the actual component data, an interactive
 * tab (0 for persistent) and a render order (the higher this value, the later
 * it is rendered).
 */
typedef struct Widget_s {
    char id[256];    /** Widget identifier. */
    WidgetType type; /**< A type of widget. */
    void *data;      /**< The data pertaining to the component. */
    u32 tab;         /**< Tab number in which it belongs. */
    i32 z;           /**< Rendering priority. */
} Widget;

/**
 * \brief Create a UI widget.
 * \param [in] id Widget idenfifier.
 * \param [in] type The type of widget.
 * \param [in] content A pointer to a widget data.
 * \param [in] tab The tab the widget belongs to.
 * \param [in] z The rendering priority of the widget.
 * \returns Pointer to a widget object.
 */
Widget *WidgetCreate(const char *id, WidgetType type, void *data, u32 tab,
                     i32 z);

/**
 * \brief Frees the widget memory.
 * \param [in, out] widget The widget to be freed.
 * \returns Void.
 */
void WidgetFree(Widget *widget);

/**
 * \brief Deals with the input of a widget.
 * \param [in, out] widget The widget to test input from.
 * \param [in] input An input handler.
 * \returns Void.
 */
void WidgetHandleInput(const Widget *widget, const Input *input);

/**
 * \brief Updates a widget and sets a custom glyph, typically if the widget type
 * is a canvas.
 * \param [in, out] widget The widget to be updated.
 * \returns Void.
 */
void WidgetUpdate(Widget *widget, Glyph *glyph);

/**
 * \brief Renders a widget.
 * \param [in] widget Widget to render.
 * \param [in] wind Window to render to.
 * \param [in] tex Texture to render from.
 * \returns Void.
 */
void WidgetRender(const Widget *widget, const Window *wind, const Texture *tex);

/**
 * \brief Sorts a set of widgets by ascending render order.
 * \param [in] a The first comparator.
 * \param [in] b The second comparator.
 * \returns Swap behaviour.
 */
int WidgetSort(const void *a, const void *b);

/**
 * \brief Finds a widget based on its identifier.
 * \param [in] widgets An array of widgets to search.
 * \param [in] id The widget identifier to search against.
 * \returns A found widget, or otherwise NULL.
 */
Widget *WidgetFind(Widget **widgets, const char *id);

#endif