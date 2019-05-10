/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file button.c
 *
 * \brief A UI component which allows user input from the mouse.
 *
 * \author Anthony Mercer
 *
 */

#include "interface/button.h"

/**
 * \desc First allocates the memory for the button and sets its ID. A check is
 * made for the label position: if there is no border, the label is placed at
 * (x, y); otherwise, the label is shifted down and right by a glyph to make
 * room for the border. Similarly the width and height of the button are set
 * such that, width is the length of the text and height is a single glyph in
 * the case of no border. These are expanded each way by 2 glyphs when a border
 * is present. The label and panel (given their own IDs) are created, and the
 * button rectangle is converted to pixels based on glyph dimensions.
 */
Button *ButtonCreate(const char *id, const u32 sx, const u32 sy, const i32 x,
                     const i32 y, char *text, const Border border,
                     const SDL_Color text_col, const SDL_Color bord_col) {
    Button *button = Allocate(sizeof(Button));
    strcpy(button->id, id);
    const i32 len = strlen(text);

    const i32 label_x = border == NONE ? x : x + 1;
    const i32 label_y = border == NONE ? y : y + 1;
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = border == NONE ? len : len + 2;
    button->rect.h = border == NONE ? 1 : 3;

    char label_id[256];
    strcpy(label_id, button->id);
    strcat(label_id, "_label");
    Label *label =
        LabelCreate(label_id, sx, sy, label_x, label_y, text, text_col, BLACK);
    button->label = label;

    char panel_id[256];
    strcpy(panel_id, button->id);
    strcat(panel_id, "_panel");
    Panel *panel =
        PanelCreate(panel_id, sx, sy, button->rect, border, bord_col);
    button->panel = panel;

    button->hovering = false;
    button->impressed = false;
    button->pressed = false;
    button->rect = (SDL_Rect){button->rect.x * sx, button->rect.y * sy,
                              button->rect.w * sx, button->rect.h * sy};

    return button;
}

/**
 * \desc Frees the button memory, first by freeing the label and panel, then the
 * button pointer itself.
 */
void ButtonFree(Button *button) {
    LabelFree(button->label);
    PanelFree(button->panel);
    Free(button);
}

/**
 * \desc Checks for user input on a button. Only if the user is hovering over
 * the button are the impressed or pressed flags set. Impressed is defined as
 * when the left mouse button is down; pressed when the left mouse button is
 * released.
 */
void ButtonHandleInput(Button *button, const Input *input) {
    if (button->hovering) {
        button->impressed = InputMouseDown(input, SDL_BUTTON_LEFT) ||
                            InputMousePressed(input, SDL_BUTTON_LEFT);
        button->pressed = InputMouseReleased(input, SDL_BUTTON_LEFT);
    }
}

/**
 * \desc Updates a buttons state. If the mouse cursor is within a buttons
 * boundary, the hovering state is set. Following this, the button is checked to
 * see if it is impressed or not, and colours are set accordingly. When no
 * hovering occurs, the hovering and impressed flags are set to false.
 */
void ButtonUpdate(Button *button) {
    const SDL_Rect rect = button->rect;
    const SDL_Point point = InputMousePos();

    if (SDL_PointInRect(&point, &rect)) {
        button->hovering = true;
        if (button->impressed) {
            ButtonSetColor(button, BEIGE);
        } else {
            ButtonSetColor(button, DARKGREY);
        }
    } else {
        button->hovering = false;
        button->impressed = false;
        ButtonSetColor(button, BLACK);
    }
}

/**
 * \desc Performs a check to see if a button is pressed. This is done using the
 * pressed flag as well as a chosen button ID. This allows different buttons to
 * be checked and different behaviour to be issued.
 */
bool ButtonIsPressed(const Button *button, const char *id) {
    return button->pressed && !(strcmp(button->id, id));
}

/**
 * \desc Set the background colour of all glyphs contained by a button,
 * including the label and border (if it exists).
 */
void ButtonSetColor(Button *button, const SDL_Color col) {
    for (u32 i = 0; i < (u32)ArrayCount(button->label->glyphs); ++i) {
        button->label->glyphs[i]->bg = col;
    }

    for (u32 i = 0; i < (u32)ArrayCount(button->panel->glyphs); ++i) {
        button->panel->glyphs[i]->bg = col;
    }
}