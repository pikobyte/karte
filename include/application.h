/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file application.h
 *
 * \brief The application is where the main systems are initialised and the
 * update-render loop is started.
 *
 * \author Anthony Mercer
 *
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "definitions.h"
#include "editor.h"
#include "input.h"
#include "timer.h"
#include "utils.h"
#include "window.h"

/**
 * \brief Holds pointers to systems and timing data.
 *
 * The application is the main component of the program. It has its own pointers
 * to many of the programs systems (e.g. graphics and input) and also keeps
 * track of important timing data. On creation, the main systems are
 * initialised. The running of the application performs the main loop: input,
 * update, render.
 */
typedef struct Application_s {
    u64 frames;         /**< The number of passed frames. */
    f64 fps;            /**< The current frames-per-second. */
    f64 dt;             /**< Time between frames. */
    f64 exec_time;      /**< Total execution time. */
    bool running;       /**< Running flag. */
    Editor *editor;     /**< Main editor object. */
    Input *input;       /**< Input handler to poll event. */
    Timer *fps_timer;   /**< Timer to calculate frames-per-second. */
    Timer *limit_timer; /**< Timer to limit the frames-per-second. */
    Window *wind;       /**< Main rendering window. */
} Application;

/**
 * \brief Creates the application object and initialises all systems required.
 * \returns Pointer to an application object.
 */
Application *ApplicationCreate(void);

/**
 * \brief Frees up the memory of game systems and the application itself.
 * \param [out] app The application to be freed.
 * \returns Void.
 */
void ApplicationFree(Application *app);

/**
 * \brief Starts the main application loop.
 * \param [in, out] app The application to be run.
 * \returns Void.
 */
void ApplicationRun(Application *app);

/**
 * \brief Updates the input handler and deals with global input.
 * \param [in, out] app The corresponding application.
 * \returns Void.
 */
void ApplicationHandleInput(Application *app);

/**
 * \brief Updates the systems of the application.
 * \param [in, out] app The corresponding application.
 * \returns Void.
 */
void ApplicationUpdate(Application *app);

/**
 * \brief Renders the systems of the application.
 * \param [in, out] app The corresponding application.
 * \returns Void.
 */
void ApplicationRender(const Application *app);

/**
 * \brief Performs pre-frame timing.
 * \param [in, out] app The corresponding application.
 * \returns Void.
 */
void ApplicationPreFrame(Application *app);

/**
 * \brief Performs post-frame timing.
 * \param [in, out] app The corresponding application.
 * \returns Void.
 */
void ApplicationPostFrame(Application *app);

#endif