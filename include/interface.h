/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file interface.h
 *
 * \brief The user interface components and behaviour are stored and handled
 * here.
 *
 * \author Anthony Mercer
 *
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include "button.h"
#include "canvas.h"
#include "color.h"
#include "definitions.h"
#include "glyph.h"
#include "input.h"
#include "label.h"
#include "panel.h"
#include "utils.h"
#include "widget.h"

/**
 * \brief An interface is with what the user interacts with in the program.
 *
 * The UI contains a various widgets (labels, buttons etc.) which allow the user
 * to interact with the program. Stored also are the dimensions of the currently
 * loaded glyphs, whether a ghost glyph should be shown and  the currently
 * active tab.
 */
typedef struct Interface_s {
    u32 sx;           /**< Glyph width. */
    u32 sy;           /**< Glyph height. */
    Widget **widgets; /**< List of UI widgets. */
    Glyph *cur_glyph; /**< Currently selected glyph. */
    bool show_ghost;  /**< Flag to show current glyph on a canvas. */
    u32 active_tab;   /**< Currently activated tab. */
} Interface;

/**
 * \brief Create a user interface.
 * \param [in] sx The width of a glyph.
 * \param [in] sy The height of a glyph.
 * \returns Pointer to an interface object.
 */
Interface *InterfaceCreate(u32 sx, u32 sy);

/**
 * \brief Create a button at a given position with a given colour.
 * \param [in, out] itfc The interface to be freed.
 * \returns Void.
 */
void InterfaceFree(Interface *itfc);

/**
 * \brief Handles any input regarding the UI.
 * \param [in, out] itfc The interface to check input for.
 * \param [in, out] input An input handler.
 * \returns Void.
 */
void InterfaceHandleInput(Interface *itfc, Input *input);

/**
 * \brief Updates a user interface.
 * \param [in, out] itfc The interface to be updated.
 * \returns Void.
 */
void InterfaceUpdate(Interface *itfc);

/**
 * \brief Renders a user interface.
 * \param [in] itfc The interface to be updated.
 * \param [in] wind The window to render the interface to.
 * \param [in] tex The texture to render the interface from.
 * \returns Void.
 */
void InterfaceRender(const Interface *itfc, const Window *wind,
                     const Texture *tex);

#endif