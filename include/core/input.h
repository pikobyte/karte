/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file input.h
 *
 * \brief Input is performed by polling events at every frame. Keyboard and
 * mouse inputs are stored in two arrays so that key presses and held-down
 * inputs can be handled.
 *
 * \author Anthony Mercer
 *
 */

#ifndef INPUT_H
#define INPUT_H

#include "core/common.h"
#include "core/utils.h"

#define NUM_KEYS 256
#define NUM_BUTTONS 16

/**
 * \brief Holds keyboard and mouse data.
 *
 * The input object holds current and previous inputs from the keyboard and
 * mouse so that single key presses and held-down inputs can be recorded. The
 * modifier map states what combination of modifier keys are held at a given
 * time. The mouse wheel movement is also stored.
 */
typedef struct Input_s
{
    bool curr_key_map[NUM_KEYS];      /**< Currently pressed keyboard. */
    bool prev_key_map[NUM_KEYS];      /**< Previously pressed keyboard. */
    u16 curr_mod_map;                 /**< Currently pressed modifiers. */
    u16 prev_mod_map;                 /**< Previously pressed modifiers. */
    bool curr_mouse_map[NUM_BUTTONS]; /**< Currently pressed mouse. */
    bool prev_mouse_map[NUM_BUTTONS]; /**< Previously pressed mouse. */
    f64 mouse_dx;                     /**< Change in mouse x-position. */
    f64 mouse_dy;                     /**< Change in mouse y-position. */
    i32 mouse_wheel;                  /**< Mouse wheel change. */
    bool quit;                        /**< Flag to quit application. */
    SDL_Point conversion;             /**< Conversion to pixel co-ordinates. */
} Input;

/**
 * \brief Allocates memory for the input.
 * \returns A pointer to an input object.
 */
Input *InputCreate();

/**
 * \brief Frees the input memory.
 * \param [in, out] The input to be freed.
 * \returns Void.
 */
void InputFree(Input *input);

/**
 * \brief Polls for events.
 * \param [in, out] The input object to be polled.
 * \returns Void.
 */
void InputUpdate(Input *input);

/* -----------------------------------------------------------------------------
 * KEYBOARD
 * -------------------------------------------------------------------------- */
/**
 * \brief Checks whether a keyboard button is pressed.
 * \param [in] input A pointer to an input handler.
 * \param [in] key A keyboard key code to check.
 * \returns Whether the current key is pressed.
 */
bool InputKeyPressed(const Input *input, u32 key);

/**
 * \brief Checks whether a keyboard modifier button is pressed.
 * \param [in] input A pointer to an input handler.
 * \param [in] mod A keyboard modifier combination to check.
 * \returns Whether the current modifier combination is pressed.
 */
bool InputModPressed(const Input *input, u16 mod);

/**
 * \brief Checks whether a keyboard button is held down.
 * \param [in] input A pointer to an input handler.
 * \param [in] key A keyboard key code to check.
 * \returns Whether the current key is held down.
 */
bool InputKeyHeld(const Input *input, u32 key);

/**
 * \brief Checks whether a keyboard key was pressed or was held down.
 * \param [in] input A pointer to an input handler.
 * \param [in] button A keyboard key code to check.
 * \returns Whether the current keyboard key was pressed or is held down.
 */
bool InputKeyDown(const Input *input, u32 button);

/**
 * \brief Checks whether a keyboard modifier button is held down.
 * \param [in] input A pointer to an input handler.
 * \param [in] mod A keyboard modifier combination to check.
 * \returns Whether the current modifier combination is held down.
 */
bool InputModDown(const Input *input, u16 mod);

/**
 * \brief Checks whether a keyboard button is released.
 * \param [in] input A pointer to an input handler.
 * \param [in] key A keyboard key code to check.
 * \returns Whether the current key is released.
 */
bool InputKeyReleased(const Input *input, u32 key);

/**
 * \brief Checks whether a keyboard modifier button is released.
 * \param [in] input A pointer to an input handler.
 * \param [in] mod A keyboard modifier combination to check.
 * \returns Whether the current modifier combination is released.
 */
bool InputModReleased(const Input *input, u16 mod);

/* -----------------------------------------------------------------------------
 * MOUSE
 * -------------------------------------------------------------------------- */
/**
 * \brief Checks whether a mouse button is pressed.
 * \param [in] input A pointer to an input handler.
 * \param [in] button A mouse button code to check.
 * \returns Whether the current mouse button is pressed.
 */
bool InputMousePressed(const Input *input, u32 button);

/**
 * \brief Checks whether a mouse button is held down.
 * \param [in] input A pointer to an input handler.
 * \param [in] button A mouse button code to check.
 * \returns Whether the current mouse button is held down.
 */
bool InputMouseHeld(const Input *input, u32 button);

/**
 * \brief Checks whether a mouse button was pressed or was held down.
 * \param [in] input A pointer to an input handler.
 * \param [in] button A mouse button code to check.
 * \returns Whether the current mouse button was pressed or is held down.
 */
bool InputMouseDown(const Input *input, u32 button);

/**
 * \brief Checks whether a mouse button is released.
 * \param [in] input A pointer to an input handler.
 * \param [in] button A mouse button code to check.
 * \returns Whether the current mouse button is released.
 */
bool InputMouseReleased(const Input *input, u32 button);

/**
 * \brief Determines if the mouse is within a rectangle in glyph co-ordinates.
 * \param [in] input A pointer to an input handler.
 * \param [in] rect The rectangle to check with position and dimensions in glyph
 * co-ordinates.
 * \returns Whether the mouse is within the rectangle.
 */
bool InputMouseWithin(const Input *input, SDL_Rect rect);

/**
 * \brief Gets the x-position of the mouse in pixels.
 * \returns The x-position of the mouse in pixels.
 */
u32 InputMouseX(void);

/**
 * \brief Gets the y-position of the mouse in pixels.
 * \returns The y-position of the mouse in pixels.
 */
u32 InputMouseY(void);

/**
 * \brief Gets the position of the mouse in pixels.
 * \returns The position stored as an SDL_Point.
 */
SDL_Point InputMousePos(void);

/**
 * \brief Snaps the mouse x-position to a given division.
 * \param [in] snap The value to snap to.
 * \returns The snapped x-position of the mouse in pixels, or zero if snap is
 * zero.
 */
u32 InputMouseSnapX(u32 snap);

/**
 * \brief Snaps the mouse y-position to a given division.
 * \param [in] snap The value to snap to.
 * \returns The snapped y-position of the mouse in pixels, or zero if snap is
 * zero.
 */
u32 InputMouseSnapY(u32 snap);

/**
 * \brief Snaps the mouse position to a given division.
 * \param [in] snap_x The x-position value to snap to.
 * \param [in] snap_y The x-position value to snap to.
 * \returns An x-y pair stored as an SDL_Point storing the snapped position of
 * the mouse in pixels. If either snap_x or snap_y are zero, a zero'ed point is
 * returned.
 */
SDL_Point InputMouseSnap(u32 snap_x, u32 snap_y);

/**
 * \brief Snaps the mouse position to glyph dimensions.
 * \param [in] input A pointer to an input handler.
 * \returns An x-y pair stored as an SDL_Point storing the snapped position of
 * the mouse in pixels. If either snap_x or snap_y are zero, a zero'ed point is
 * returned.
 */
SDL_Point InputMouseSnapToGlyph(const Input *input);

#endif