/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file window.c
 *
 * \brief The window is a wrapper around an SDL window and rendering context,
 * but also holds information like dimension and title.
 *
 * \author Anthony Mercer
 *
 */

#include "graphics/window.h"

/**
 * \desc Allocates the memory required by the window and sets its initial
 * dimensions and title. An SDL context is then created for the window and
 * renderer, where the clear colour is set to black. Finally, a pointer to the
 * window is returned.
 */
Window *WindowCreate(void) {
    Window *wind = Allocate(sizeof(Window));

    wind->width = 1280;
    wind->height = 720;
    wind->full_screen = false;
    wind->v_sync = true;
    strcpy(wind->title, "Karte");

    wind->sdl_window = SDL_CreateWindow(
        wind->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        wind->width, wind->height, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);

    if (wind->sdl_window == NULL) {
        Log(LOG_FATAL, "Could not initialise SDL_Window!");
    }

    wind->sdl_renderer = SDL_CreateRenderer(wind->sdl_window, -1,
                                            SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
    if (wind->sdl_renderer == NULL) {
        Log(LOG_FATAL, "Could not initialise SDL_Renderer!");
    }
    SDL_SetRenderDrawColor(wind->sdl_renderer, 0x00, 0x00, 0x00, 0x00);

    return wind;
}

/**
 * \desc Frees the memory pointed to by a window. The SDL context memory is also
 * freed here.
 */
void WindowFree(Window *wind) {
    SDL_DestroyRenderer(wind->sdl_renderer);
    SDL_DestroyWindow(wind->sdl_window);
    Free(wind);
}

/**
 * \desc Clears the SDL renderer context held by a window to a single colour.
 * This colour is set in the window creation.
 */
void WindowClear(const Window *wind) { SDL_RenderClear(wind->sdl_renderer); }

/**
 * \desc Updates the SDL renderer with any of the drawn graphics since the
 * previous call.
 */
void WindowFlip(const Window *wind) { SDL_RenderPresent(wind->sdl_renderer); }

/**
 * \desc Sets the string for the windows title bar. A formatted string is passed
 * in, and any additional parameters are used for that formatted string.
 * Finally, the window's own title record is updated as well as the SDL_Windows.
 */
void WindowSetTitle(Window *wind, const char *str, ...) {
    char title[64] = {0};
    sprintf(title, "%s", str);

    va_list ap;
    va_start(ap, str);
    vsnprintf(title, 63, str, ap);
    va_end(ap);

    strcpy(wind->title, title);
    SDL_SetWindowTitle(wind->sdl_window, title);
}