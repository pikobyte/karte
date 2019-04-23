/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file application.c
 *
 * \brief The application is where the main systems are initialised and the
 * update-render loop is started.
 *
 * \author Anthony Mercer
 *
 */

#include "application.h"

/**
 * \desc Begins by allocating the memory for the application. The systems used
 * by the application are then initialised, the running flag is set to true, and
 * the memory is returned.
 */
Application *ApplicationCreate(void) {
    Application *app = Allocate(sizeof(Application));
    Log(LOG, "Created application at %p.", app);

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        Log(FATAL, "Could not initialise SDL2: %s", SDL_GetError());
    }

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        Log(FATAL, "Could not initialise SDL_image: %s", IMG_GetError());
    }

    if (TTF_Init()) {
        Log(FATAL, "Could not initialise SDL_ttf: %s", TTF_GetError());
    }

    app->running = true;

    return app;
}

/**
 * \desc Frees all of the memory that the application allocates and ends by
 * freeing the memory of the application itself.
 */
void ApplicationFree(Application *app) {
    IMG_Quit();
    TTF_Quit();
    SDL_AudioQuit();
    SDL_VideoQuit();
    SDL_Quit();
    Free(app);
}

/**
 * \desc Executes the application through a loop which, whilst the running flag
 * is set, performs timing calculations, handles input, and updates and renders
 * the application. The length of execution time in seconds is logged after
 * this.
 */
void ApplicationRun(Application *app) {
    while (app->running) {
        ApplicationPreFrame(app);
        ApplicationHandleInput(app);
        ApplicationUpdate(app);
        ApplicationRender(app);
        ApplicationPostFrame(app);
        app->running = false;
    }

    Log(LOG, "Execution time: %.3f s", app->exec_time);
}

/**
 * \desc Updates the application's input handler and checks for any global
 * input. This is where user input can result in the application closing.
 */
void ApplicationHandleInput(Application *app) { UNUSED(app); }

/**
 * \desc Updates the application state i.e. where all logic is performed.
 */
void ApplicationUpdate(Application *app) { UNUSED(app); }

/**
 * \desc Renders the application by clearing the window, drawing to it and then
 * flipping the buffers.
 */
void ApplicationRender(const Application *app) { UNUSED(app); }

/**
 * \desc Calculates timing before the new frame has begun and also sets the
 * application frames-per-second.
 */
void ApplicationPreFrame(Application *app) { UNUSED(app); }

/**
 * \desc Calculates timing after the frame has ended, updating the window title
 * to display frames-per-second and then delays the application to cap to the
 * target FPS.
 */
void ApplicationPostFrame(Application *app) { UNUSED(app); }