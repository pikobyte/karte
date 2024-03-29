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

#include "core/application.h"
#include "core/common.h"
#include "core/utils.h"

u32 g_mem_allocs = 0;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    Application* app = ApplicationCreate();

    ApplicationRun(app);
    ApplicationFree(app);

    Log(LOG_NOTIFY, "Allocations remaining: %u", g_mem_allocs);

    return EXIT_SUCCESS;
}