/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file input.c
 *
 * \brief Input is performed by polling events at every frame. Keyboard and
 * mouse inputs are stored in two arrays so that key presses and held-down
 * inputs can be handled.
 *
 * \author Anthony Mercer
 *
 */

#include "input.h"

/**
 * \desc Allocates the memory for the input object and nothing more.
 */
Input *InputCreate(void) {
    Input *input = Allocate(sizeof(Input));
    Log(LOG, "Created input at %p.", input);
    return input;
}

/**
 * \desc Frees the memory for an input object and nothing more.
 */
void InputFree(Input *input) { Free(input); }

/**
 * \desc Polls for a variety of events and returns an exit condition based on
 * window closure. The previous key/button inputs are stored (including modifier
 * keys) and the mouse wheel is reset. The new key/button inputs are set based
 * on either down presses or up releases.
 */
bool InputUpdate(Input *input) {
    for (u32 i = 0; i < NUM_KEYS; ++i) {
        input->prev_key_map[i] = input->curr_key_map[i];
    }

    for (u32 i = 0; i < NUM_BUTTONS; ++i) {
        input->prev_mouse_map[i] = input->curr_mouse_map[i];
    }

    input->prev_mod_map = input->curr_mod_map;
    input->curr_mod_map = SDL_GetModState();

    input->mouse_wheel = 0;
    input->mouse_dx = 0.0;
    input->mouse_dy = 0.0;

    SDL_Event e = {0};
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            return false;
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym > NUM_KEYS)
                break;
            input->curr_key_map[e.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            if (e.key.keysym.sym > NUM_KEYS)
                break;
            input->curr_key_map[e.key.keysym.sym] = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button > NUM_BUTTONS)
                break;
            input->curr_mouse_map[e.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button > NUM_BUTTONS)
                break;
            input->curr_mouse_map[e.button.button] = false;
            break;
        case SDL_MOUSEWHEEL:
            input->mouse_wheel = e.wheel.y;
            break;
        case SDL_MOUSEMOTION:
            input->mouse_dx = (float)e.motion.xrel;
            input->mouse_dy = (float)e.motion.yrel;
            break;
        default:
            break;
        }
    }

    return true;
}

/* -----------------------------------------------------------------------------
 * KEYBOARD
 * -------------------------------------------------------------------------- */
/**
 * \desc First a check is performed to see if the provided keyboard key is in
 * range. If it is, then the return is if the current key is currently down and
 * wasn't in the previous frame.
 */
bool InputKeyPressed(const Input *input, const u32 key) {
    if (key > NUM_KEYS) {
        return false;
    }
    return (input->curr_key_map[key] && !input->prev_key_map[key]);
}

/**
 * \desc SDL modifier keys are stored as a bit field: if the current modifier
 * key is currently down and wasn't in the previous frame, only then return
 * true.
 */
bool InputModPressed(const Input *input, const u16 mod) {
    return (input->curr_mod_map & mod) && !(input->prev_mod_map & mod);
}

/**
 * \desc First a check is performed to see if the provided keyboard key is in
 * range. If it is, then the return is if the current key is currently down and
 * was also in the previous frame.
 */
bool InputKeyDown(const Input *input, const u32 key) {
    if (key > NUM_KEYS) {
        return false;
    }
    return (input->curr_key_map[key] && input->prev_key_map[key]);
}

/**
 * \desc SDL modifier keys are stored as a bit field: if the current modifier
 * key is currently down and was also in the previous frame, only then return
 * true.
 */
bool InputModDown(const Input *input, const u16 mod) {
    return (input->curr_mod_map & mod) && (input->prev_mod_map & mod);
}

/**
 * \desc First a check is performed to see if the provided keyboard key is in
 * range. If it is, then the return is if the current key is not currently down
 * but was in the previous frame.
 */
bool InputKeyReleased(const Input *input, const u32 key) {
    if (key > NUM_KEYS) {
        return false;
    }
    return (!input->curr_key_map[key] && input->prev_key_map[key]);
}

/**
 * \desc SDL modifier keys are stored as a bit field: if the current modifier
 * key is not currently down but was in the previous frame, only then return
 * true.
 */
bool InputModReleased(const Input *input, const u16 mod) {
    return !(input->curr_mod_map & mod) && (input->prev_mod_map & mod);
}

/* -----------------------------------------------------------------------------
 * MOUSE
 * -------------------------------------------------------------------------- */
/**
 * \desc First a check is performed to see if the provided mouse button is in
 * range. If it is, then the return is if the current button is currently down
 * and wasn't in the previous frame.
 */
bool InputMousePressed(const Input *input, const u32 button) {
    if (button > NUM_BUTTONS) {
        return false;
    }
    return (input->curr_mouse_map[button] && !input->prev_mouse_map[button]);
}

/**
 * \desc First a check is performed to see if the provided mouse button is in
 * range. If it is, then the return is if the current button is currently down
 * and was also in the previous frame.
 */
bool InputMouseDown(const Input *input, const u32 button) {
    if (button > NUM_BUTTONS) {
        return false;
    }
    return (input->curr_mouse_map[button] && input->prev_mouse_map[button]);
}

/**
 * \desc First a check is performed to see if the provided mouse button is in
 * range. If it is, then the return is if the current button is not currently
 * down but was in the previous frame.
 */
bool InputMouseReleased(const Input *input, const u32 button) {
    if (button > NUM_BUTTONS) {
        return false;
    }
    return (!input->curr_mouse_map[button] && input->prev_mouse_map[button]);
}

/**
 * \desc Returns the x-position of the mouse in pixels, where (0, 0) corresponds
 * to the top left of the screen.
 */
u32 InputMouseX(void) {
    i32 x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    return (u32)x;
}

/**
 * \desc Returns the y-position of the mouse in pixels, where (0, 0) corresponds
 * to the top left of the screen.
 */
u32 InputMouseY(void) {
    i32 x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    return (u32)y;
}

/**
 * \desc Snaps the x-position of the mouse to some division. This essentially
 * rounds the mouse x-position and returns this rounded value.
 */
u32 InputMouseSnapX(const u32 snap) {
    i32 x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    return (u32)((x / snap) * snap);
}

/**
 * \desc Snaps the y-position of the mouse to some division. This essentially
 * rounds the mouse y-position and returns this rounded value.
 */
u32 InputMouseSnapY(const u32 snap) {
    i32 x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    return (u32)((y / snap) * snap);
}