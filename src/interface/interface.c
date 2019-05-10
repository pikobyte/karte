/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file interface.c
 *
 * \brief The user interface components and behaviour are stored and handled
 * here.
 *
 * \author Anthony Mercer
 *
 */

#include "interface/interface.h"

/**
 * \desc Begins by allocating memory for the interface and assigning glyph
 * dimensions. The interface components are then created after this and push
 * into the interface arrays.
 * TODO: Load from a JSON file or something similar.
 */
Interface *InterfaceCreate(const u32 sx, const u32 sy) {
    Interface *itfc = Allocate(sizeof(Interface));
    Log(LOG, "Created interface at %p.", itfc);
    itfc->sx = sx;
    itfc->sy = sy;

    Button *b1 = ButtonCreate("quit_button", sx, sy, 2, 40, "Quit", SINGLE,
                              GREY, LIGHTGREY);
    Button *b2 = ButtonCreate("log_button", sx, sy, 8, 40, "Log", SINGLE, GREY,
                              LIGHTGREY);
    ArrayPush(itfc->buttons, b1);
    ArrayPush(itfc->buttons, b2);

    Label *l1 =
        LabelCreate("title", sx, sy, 8, 1, "Karte v0.01", DARKGREY, LIGHTGREY);
    ArrayPush(itfc->labels, l1);

    Panel *p1 = PanelCreate("options", sx, sy, (SDL_Rect){1, 1, 25, 43}, SINGLE,
                            LIGHTGREY);
    Panel *p2 = PanelCreate("editor", sx, sy, (SDL_Rect){26, 1, 53, 43}, SINGLE,
                            LIGHTGREY);
    ArrayPush(itfc->panels, p1);
    ArrayPush(itfc->panels, p2);

    return itfc;
}

/**
 * \desc Frees the interface memory by iterating through the interface
 * components, freeing each, freeing each array and finally the interface
 * pointer.
 */
void InterfaceFree(Interface *itfc) {
    for (i32 i = 0; i < ArrayCount(itfc->buttons); ++i) {
        ButtonFree(itfc->buttons[i]);
    }
    ArrayFree(itfc->buttons);

    for (i32 i = 0; i < ArrayCount(itfc->labels); ++i) {
        LabelFree(itfc->labels[i]);
    }
    ArrayFree(itfc->labels);

    for (i32 i = 0; i < ArrayCount(itfc->panels); ++i) {
        PanelFree(itfc->panels[i]);
    }
    ArrayFree(itfc->panels);

    Free(itfc);
}

/**
 * \desc Handles the input for interactable UI components. The interactions are
 * based on component state and a provided component identifier which allows for
 * singular component behaviour.
 */
void InterfaceHandleInput(Interface *itfc, Input *input) {
    for (i32 i = 0; i < ArrayCount(itfc->buttons); ++i) {
        ButtonHandleInput(itfc->buttons[i], input);
        if (ButtonIsPressed(itfc->buttons[i], "quit_button")) {
            input->quit = true;
        }

        if (ButtonIsPressed(itfc->buttons[i], "log_button")) {
            Log(LOG, "Button %s pressed!", itfc->buttons[i]->id);
        }
    }
}

/**
 * \desc Updates the UI components that need it. This is typically changes in
 * component state as well as visual appearance for user feedback.
 */
void InterfaceUpdate(Interface *itfc) {
    for (i32 i = 0; i < ArrayCount(itfc->buttons); ++i) {
        ButtonUpdate(itfc->buttons[i]);
    }
}

/**
 * \desc Renders the whole interface by iterating through each component. The UI
 * panels are rendered first, then buttons and finally labels.
 * TODO: Update given different types of component.
 */
void InterfaceRender(const Interface *itfc, const Window *wind,
                     const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(itfc->panels); ++i) {
        PanelRender(itfc->panels[i], wind, tex);
    }

    for (i32 i = 0; i < ArrayCount(itfc->buttons); ++i) {
        ButtonRender(itfc->buttons[i], wind, tex);
    }

    for (i32 i = 0; i < ArrayCount(itfc->labels); ++i) {
        LabelRender(itfc->labels[i], wind, tex);
    }
}