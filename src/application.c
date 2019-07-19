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
    Log(LOG_NOTIFY, "Created application at %p.", app);

    strcpy(g_dir, ApplicationDir());

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        Log(LOG_FATAL, "Could not initialise SDL2: %s", SDL_GetError());
    }

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        Log(LOG_FATAL, "Could not initialise SDL_image: %s", IMG_GetError());
    }

    if (TTF_Init()) {
        Log(LOG_FATAL, "Could not initialise SDL_ttf: %s", TTF_GetError());
    }

    app->input = InputCreate();
    app->fps_timer = TimerCreate();
    app->limit_timer = TimerCreate();
    app->res = ResourcerCreate();
    app->wind = WindowCreate();
    app->editor = EditorCreate(app->wind, app->res);
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

    EditorFree(app->editor);
    WindowFree(app->wind);
    ResourcerFree(app->res);
    TimerFree(app->limit_timer);
    TimerFree(app->fps_timer);
    InputFree(app->input);
    Free(app);
}

/**
 * \desc Executes the application through a loop which, whilst the running flag
 * is set, performs timing calculations, handles input, and updates and renders
 * the application. The length of execution time in seconds is logged after
 * this.
 */
void ApplicationRun(Application *app) {
    TimerStart(app->fps_timer);

    while (app->running) {
        ApplicationPreFrame(app);
        ApplicationHandleInput(app);
        ApplicationUpdate(app);
        ApplicationRender(app);
        ApplicationPostFrame(app);
    }

    Log(LOG_NOTIFY, "Execution time: %.3f s", app->exec_time);
}

/**
 * \desc Updates the application's input handler and checks for any global
 * input. This is where user input can result in the application closing.
 */
void ApplicationHandleInput(Application *app) {
    InputUpdate(app->input);
    if (app->input->quit) {
        app->running = false;
    }

    EditorHandleInput(app->editor, app->input);
}

/**
 * \desc Updates the application state i.e. where all logic is performed.
 */
void ApplicationUpdate(Application *app) { EditorUpdate(app->editor); }

/**
 * \desc Renders the application by clearing the window, drawing to it and then
 * flipping the buffers.
 */
void ApplicationRender(const Application *app) {
    WindowClear(app->wind);
    EditorRender(app->editor, app->wind);
    WindowFlip(app->wind);
}

/**
 * \desc Calculates timing before the new frame has begun and also sets the
 * application frames-per-second.
 */
void ApplicationPreFrame(Application *app) {
    app->dt = TimerGetTicks(app->limit_timer) / 1000.0;
    TimerStart(app->limit_timer);

    const f64 seconds = TimerGetTicks(app->fps_timer) / 1000.0;
    app->fps = app->frames / seconds;
}

/**
 * \desc Calculates timing after the frame has ended, updating the window title
 * to display frames-per-second and then delays the application to cap to the
 * target FPS, provided v-sync is turned off.
 */
void ApplicationPostFrame(Application *app) {
    const u64 ticks = TimerGetTicks(app->limit_timer);
    if (!app->wind->v_sync && ticks < (1000.0 / 60.0)) {
        SDL_Delay((1000 / 60) - (u32)ticks);
    }

    if (app->frames++ % 24 == 0) {
        WindowSetTitle(app->wind, "Karte | FPS: %d", (u32)app->fps);
    }

    app->exec_time += app->dt;
}

/**
 * \desc Concatenates the home directory (Linux) with the absolute path of the
 * project directory.
 * FIXME: The absolute directory (CWD) needs to adapt to user/install path in
 * release mode.
 */
char *ApplicationDir(void) {
    char *home = getenv("HOME");
    if (home) {
        strcat(home, CWD);
    }
    return home;
}