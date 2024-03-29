/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file timer.h
 *
 * \brief Handles timers by allowing the accumulation of retrieval of passed
 * milliseconds.
 *
 * \author Anthony Mercer
 *
 */

#ifndef TIMER_H
#define TIMER_H

#include "core/common.h"
#include "core/utils.h"

/**
 * \brief A timer allows the accumulation of ticks via starting and pausing.
 *
 * Timers can be started, at which point the number of ticks since SDL
 * initialisation are retrieved. Pausing gathers ticks separately.
 */
typedef struct [[nodiscard]]
{
    u64 start_ticks;  /**< Ticks since timer was started. */
    u64 paused_ticks; /**< Ticks since timer was paused. */
    bool started;     /**< Flag for started. */
    bool paused;      /**< Flag for paused. */
} Timer;

/**
 * \brief Allocates memory for the timer.
 * \returns Pointer to a timer object.
 */
[[nodiscard]] Timer* TimerCreate(void);

/**
 * \brief Frees memory for a timer.
 * \param [in, out] timer The timer to be freed.
 * \returns Void.
 */
void TimerFree(Timer* timer);

/**
 * \brief Starts a timer to accumulate ticks.
 * \param [in, out] timer The timer to be started.
 * \returns Void.
 */
void TimerStart(Timer* timer);

/**
 * \brief Pauses a timer.
 * \param [in, out] timer The timer to be paused.
 * \returns Void.
 */
void TimerPause(Timer* timer);

/**
 * \brief Retrieves the number of accumulated ticks.
 * param [in] timer The timer to read ticks from.
 * \returns Ticks accumulated.
 */
[[nodiscard]] u64 TimerGetTicks(const Timer* timer);

#endif