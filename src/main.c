/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file main.c
 *
 * \brief The program main entry point. Creates, runs and cleans up the Karte
 * application.
 *
 * \author Anthony Mercer
 *
 * \mainpage
 * Karte is a simple tool which can be used to create ASCII art and tilemaps
 * through the inclusion of tile properties. It is designed to be a Linux
 * alternative to REXPaint.
 */

#include "application.h"
#include "definitions.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    Application *app = ApplicationCreate();

    ApplicationRun(app);
    ApplicationFree(app);

    Log(LOG_NOTIFY, "Allocations remaining: %u", g_mem_allocs);

    UNUSED(argc);
    UNUSED(argv);

    return 0;
}