/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file button.h
 *
 * \brief A UI component which allows user input. The behaviour of a button
 * press is described retroactively: only the press of a button is checked here.
 * Buttons can be active or inactive, and in the former case, undergo the
 * following behaviour: hovered, impressed and pressed. The latter two cases
 * represent input presses and input releases respectively. Button presses are
 * only registered when input is released whilst hovering over that button.
 *
 * \author Anthony Mercer
 *
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "core/common.h"
#include "core/input.h"
#include "core/utils.h"
#include "graphics/color.h"
#include "graphics/glyph.h"
#include "graphics/texture.h"
#include "graphics/window.h"
#include "memory/vector.h"
#include "ui/label.h"
#include "ui/panel.h"

/**
 * \brief Buttons can be pressed by the user to activate some functionality.
 *
 * A button has dimensions, a panel with or without a border, and a text label.
 * A button is either idle, impressed (mouse down) or pressed (mouse released).
 * The colour changes based on this state. A test for a button press is based on
 * its ID and its pressed state,
 */
typedef struct Button_s {
    Label *label;   /**< Text label. */
    Panel *panel;   /**< Panel encompassing the button. */
    bool active;    /**< Whether the button can be interacted with. */
    bool hovering;  /**< Flag for when hovering over the button. */
    bool impressed; /**< Flag for when input is held on a button. */
    bool pressed;   /**< Flag for when input is release on a button. */
} Button;

/**
 * \brief Create a button at a given position with a given colour.
 * \param [in] x The x-position of the label in glyph units.
 * \param [in] y The y-position of the label in glyph units.
 * \param [in] text The button text to display.
 * \param [in] border The border type.
 * \param [in] text_col Colour of the text.
 * \param [in] bord_col Colour of the border.
 * \param [in] active The default active state of the button.
 * \returns Pointer to a panel object.
 */
Button *ButtonCreate(i32 x, i32 y, const char *text, Border border,
                     SDL_Color text_col, SDL_Color bord_col, bool active);

/**
 * \brief Frees the button memory.
 * \param [in, out] button The button to be freed.
 * \returns Void.
 */
void ButtonFree(Button *button);

/**
 * \brief Deals with the input of a button.
 * \param [in, out] button The button to test input from.
 * \param [in] input An input handler.
 * \returns Void.
 */
void ButtonHandleInput(Button *button, const Input *input);

/**
 * \brief Updates the button, namely colour based on state.
 * \param [in, out] button The button to be updated.
 * \returns Void.
 */
void ButtonUpdate(Button *button);

/**
 * \brief Renders a button.
 * \param [in] button Button to render.
 * \param [in] wind Window to render to.
 * \param [in] tex Texture to render from.
 * \returns Void.
 */
void ButtonRender(const Button *button, const Window *wind, const Texture *tex);

/**
 * \brief Checks whether a button and chosen ID is pressed.
 * \param [in] button The button to check whether it has been pressed.
 * \returns Whether the button is pressed.
 */
bool ButtonIsPressed(const Button *button);

/**
 * \brief Changes the foreground colour of a button.
 * \param [in, out] button The button to change the colour of.
 * \param [in] col The colour to change to.
 * \returns Void.
 */
void ButtonSetForeColor(Button *button, SDL_Color col);

/**
 * \brief Changes the background colour of a button.
 * \param [in, out] button The button to change the colour of.
 * \param [in] col The colour to change to.
 * \returns Void.
 */
void ButtonSetBackColor(Button *button, SDL_Color col);

/**
 * \brief Changes the opacity of a button.
 * \param [in, out] button The button to change the opacity of.
 * \param [in] opacity The opacity to change to.
 * \returns Void.
 */
void ButtonSetOpacity(Button *button, u8 opacity);

#endif