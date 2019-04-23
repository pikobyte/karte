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
#include "utils.h"

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
    u64 frames;    /**< The number of passed frames. */
    f32 fps;       /**< The current frames-per-second. */
    f32 dt;        /**< Time between frames. */
    f32 exec_time; /**< Total execution time. */
    bool running;  /**< Running flag. */
} Application;

/**
 * \brief Creates the application object and initialises all systems required,
 * \returns Pointer to an application object.
 */
Application *ApplicationCreate(void);

/**
 * \brief Frees up the memory of game systems and the application itself.
 * \param [out] app The application to be freed.
 * \returns None.
 */
void ApplicationFree(Application *app);

/**
 * \brief Starts the main application loop.
 * \param [out] app The application to be run.
 * \returns None.
 */
void ApplicationRun(Application *app);

/**
 * \brief Updates the input handler and deals with global input.
 * \param [out] app The corresponding application.
 * \returns None.
 */
void ApplicationHandleInput(Application *app);

/**
 * \brief Updates the systems of the application.
 * \param [out] app The corresponding application.
 * \returns None.
 */
void ApplicationUpdate(Application *app);

/**
 * \brief Renders the systems of the application.
 * \param [out] app The corresponding application.
 * \returns None.
 */
void ApplicationRender(const Application *app);

/**
 * \brief Performs pre-frame timing.
 * \param [out] app The corresponding application.
 * \returns None.
 */
void ApplicationPreFrame(Application *app);

/**
 * \brief Performs post-frame timing.
 * \returns None.
 */
void ApplicationPostFrame(Application *app);

#endif