/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file main.c
 * \brief The program main entry point. Creates, runs and cleans up the Karte
 * application.
 *
 * \author Anthony Mercer
 *
 */

#include "definitions.h"
#include "utils.h"

int main(void) {
    void *all = Allocate(sizeof(int));
    Destroy(all);

    Log(LOG, "Allocations remaining: %u", g_mem_allocs);

    return 0;
}