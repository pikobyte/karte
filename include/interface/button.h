/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file button.h
 *
 * \brief A UI component which allows user input from the mouse.
 *
 * \author Anthony Mercer
 *
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "color.h"
#include "definitions.h"
#include "glyph.h"
#include "input.h"
#include "interface/label.h"
#include "interface/panel.h"
#include "utils.h"

/**
 * \brief Buttons can be pressed by the user to activate some functionality.
 *
 * A button has an identifier, dimensions, a panel with or without a border, and
 * a text label. A button is either idle, impressed (mouse down) or pressed
 * (mouse released). The colour changes based on this state. A test for a button
 * press is based on its ID and its pressed state,
 */
typedef struct Button_s {
    char id[256];
    SDL_Rect rect;
    Label *label;
    Panel *panel;
    bool hovering;
    bool impressed;
    bool pressed;
} Button;

/**
 * \brief Create a button at a given position with a given colour.
 * \params [in] id Identifier for the button.
 * \params [in] sx The width of a glyph.
 * \params [in] sy The height of a glyph.
 * \params [in] x The x-position of the label in glyph units.
 * \params [in] y The y-position of the label in glyph units.
 * \params [in] text The button text to display.
 * \params [in] border The border type.
 * \params [in] text_col Colour of the text.
 * \params [in] bord_col Colour of the border.
 * \returns Pointer to a panel object.
 */
Button *ButtonCreate(const char *id, const u32 sx, const u32 sy, const i32 x,
                     const i32 y, char *text, const Border border,
                     const SDL_Color text_col, const SDL_Color bord_col);

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
 * \brief Checks whether a button and chosen ID is pressed.
 * \param [in] button The button to check whether it has been pressed.
 * \param [in] id The ID of the button wishing to be tested.
 * \returns Whether the button is pressed.
 */
bool ButtonIsPressed(const Button *button, const char *id);

/**
 * \brief Changes the colour of a button.
 * \param [in, out] button The button to change the colour of.
 * \param [in] col The colour to change to.
 * \returns Void.
 */
void ButtonSetColor(Button *button, const SDL_Color col);

#endif