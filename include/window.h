/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file window.h
 *
 * \brief The window is a wrapper around an SDL window and rendering context,
 * but also holds information like dimension and title.
 *
 * \author Anthony Mercer
 *
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"
#include "utils.h"

/**
 * \brief Wrapper for an SDL_Window, SDL_Renderer and additional properties.
 *
 * A window allows the joint creation of the necessary SDL components used in
 * graphical rendering. Window creation fails if any of the SDL components fail
 * to do so. The typically usage for a window is the continually clear the
 * screen, render to the back-buffer, and then flip the buffers to present the
 * graphics.
 */
typedef struct Window_s {
    u32 width;                  /**< Window width in pixels. */
    u32 height;                 /**< Window height in pixels. */
    char title[64];             /**< Window title text. */
    bool full_screen;           /**< Full-screen flag. */
    bool v_sync;                /**< Vertical synchonisation flag. */
    SDL_Window *sdl_window;     /**< Pointer to the SDL window. */
    SDL_Renderer *sdl_renderer; /**< SDL rendering context. */
} Window;

/**
 * \brief Allocates memory for the window and defines the graphical context.
 * \returns Pointer to the window object.
 */
Window *WindowCreate(void);

/**
 * \brief Frees the window memory.
 * \param [in, out] The window to be freed.
 * \returns Void.
 */
void WindowFree(Window *wind);

/**
 * \brief Clears the window buffer to black.
 * \param [in] wind The window to clear.
 * \returns Void.
 */
void WindowClear(const Window *wind);

/**
 * \brief Flips the window buffers to display graphics.
 * \param [in] wind The window to display graphics of.
 * \returns Void.
 */
void WindowFlip(const Window *wind);

/**
 * \brief Sets the window title based on a formatted string.
 * \param [in, out] wind The window to set the title of.
 * \param [in] title The title to be set.
 * \param [in] ... Additional parameters for the formatted string.
 * \returns Void.
 */
void WindowSetTitle(Window *wind, const char *str, ...);

#endif