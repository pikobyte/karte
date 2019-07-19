/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file timer.c
 *
 * \brief Handles timers by allowing the accumulation and retrieval of passed
 * milliseconds.
 *
 * \author Anthony Mercer
 *
 */

#include "timer.h"

/**
 * \desc Allocates memory for a timer object and logs the memory location that
 * is given then returns a pointer to that address.
 */
Timer *TimerCreate(void) {
    Timer *timer = Allocate(sizeof(Timer));
    Log(LOG_NOTIFY, "Created timer at %p.", timer);
    return timer;
}

/**
 * \desc Frees the memory pointed to by a timer pointer. No other further
 * functionality is required.
 */
void TimerFree(Timer *timer) { Free(timer); }

/**
 * \desc Starts the timer by setting the flags appropriately, then sets
 * start_ticks to the number of milliseconds passed since SDL was initialised.
 */
void TimerStart(Timer *timer) {
    timer->started = true;
    timer->paused = false;
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
}

/**
 * \desc Checks if the timer has been started and that it is not already paused.
 * Only then pause the timer and set the appropriate paused_ticks.
 */
void TimerPause(Timer *timer) {
    if (timer->started && !timer->paused) {
        timer->paused = true;
        timer->start_ticks = 0;
        timer->paused_ticks = SDL_GetTicks();
    }
}

/**
 * \desc First checks if the timer has been started, and if it hasn't then
 * return 0. Otherwise return the appropriate amount of ticks based on whether
 * the timer is paused. The ticks are the number of milliseconds passed after
 * SDL was initialised.
 */
u64 TimerGetTicks(const Timer *timer) {
    u64 ticks = 0;

    if (!timer->started) {
        return ticks;
    }

    if (timer->paused) {
        ticks = timer->paused_ticks;
    } else {
        ticks = SDL_GetTicks() - timer->start_ticks;
    }

    return ticks;
}