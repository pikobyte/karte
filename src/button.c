/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file button.c
 *
 * \brief A UI component which allows user input. The behaviour of a button
 * press is described retroactively: only the press of a button is checked here.
 * Buttons can be active or inactive, and in the former case, undergo the
 * following behaviour: hovered, impressed and pressed. The latter two cases
 * represent input presses and input releases respectively. Button presses are
 * only registered when input is released whilst hovering over that button.
 *
 * \author Anthony Mercer
 *
 */

#include "button.h"

/**
 * \desc First allocates the memory for the button. A check is made for the
 * label position: if there is no border, the label is placed at (x, y);
 * otherwise, the label is shifted down and right by a glyph to make room for
 * the border. Similarly the width and height of the button are set such that,
 * width is the length of the text and height is a single glyph in the case of
 * no border. These are expanded each way by 2 glyphs when a border is present.
 * The label and panel (given their own IDs) are created, and the button
 * rectangle is converted to pixels based on glyph dimensions.
 */
Button *ButtonCreate(i32 x, i32 y, const char *text, Border border,
                     SDL_Color text_col, SDL_Color bord_col, bool active) {
    Button *button = Allocate(sizeof(Button));
    i32 len = (i32)strlen(text);

    i32 label_x = border == BORDER_NONE ? x : x + 1;
    i32 label_y = border == BORDER_NONE ? y : y + 1;

    button->label = LabelCreate(label_x, label_y, text, text_col, BLACK);

    SDL_Rect rect = {0};
    rect.x = x;
    rect.y = y;
    rect.w = (border == BORDER_NONE ? len : len + 2);
    rect.h = (border == BORDER_NONE ? 1 : 3);

    button->panel = PanelCreate(rect, border, bord_col);

    button->active = active;
    button->hovering = false;
    button->impressed = false;
    button->pressed = false;

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
 * \desc Checks for user input on an active button. Only if the user is hovering
 * over the button are the impressed or pressed flags set. Impressed is defined
 * as when the left mouse button is down; pressed when the left mouse button is
 * released.
 */
void ButtonHandleInput(Button *button, const Input *input) {
    if (!button->active) {
        return;
    }

    if (InputMouseWithin(input, button->panel->rect)) {
        button->hovering = true;
        if (button->impressed) {
            ButtonSetBackColor(button, BEIGE);
        } else {
            ButtonSetBackColor(button, DARKGREY);
        }
    } else {
        button->hovering = false;
        button->impressed = false;
        ButtonSetBackColor(button, BLACK);
    }

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
    if (!button->active) {
        ButtonSetOpacity(button, 64);
        return;
    } else {
        ButtonSetOpacity(button, 255);
    }
}

/**
 * \desc Renders a button to a window based on a given texture by iterating
 * through its glyphs. This is done by first rendering the border then the text.
 */
void ButtonRender(const Button *button, const Window *wind,
                  const Texture *tex) {
    for (i32 i = 0; i < ArrayCount(button->panel->glyphs); ++i) {
        GlyphRender(button->panel->glyphs[i], wind, tex);
    }

    for (i32 i = 0; i < ArrayCount(button->label->glyphs); ++i) {
        GlyphRender(button->label->glyphs[i], wind, tex);
    }
}

/**
 * \desc Performs a check to see if a button is pressed. This is done using the
 * pressed flag as well as a chosen button ID. This allows different buttons to
 * be checked and different behaviour to be issued.
 */
bool ButtonIsPressed(const Button *button) {
    const SDL_Point mpos = InputMousePos();
    SDL_Rect r = button->panel->rect;
    r.x *= 16;
    r.y *= 16;
    r.w *= 16;
    r.h *= 16;
    return button->pressed && SDL_PointInRect(&mpos, &r);
}

/**
 * \desc Sets the foreground colour of all glyphs contained by a button,
 * including the label and border (if it exists).
 */
void ButtonSetForeColor(Button *button, SDL_Color col) {
    for (i32 i = 0; i < ArrayCount(button->label->glyphs); ++i) {
        button->label->glyphs[i]->fg = col;
    }

    for (i32 i = 0; i < ArrayCount(button->panel->glyphs); ++i) {
        button->panel->glyphs[i]->fg = col;
    }
}

/**
 * \desc Sets the background colour of all glyphs contained by a button,
 * including the label and border (if it exists).
 */
void ButtonSetBackColor(Button *button, SDL_Color col) {
    for (i32 i = 0; i < ArrayCount(button->label->glyphs); ++i) {
        button->label->glyphs[i]->bg = col;
    }

    for (i32 i = 0; i < ArrayCount(button->panel->glyphs); ++i) {
        button->panel->glyphs[i]->bg = col;
    }
}

/**
 * \desc Sets the opacity of all glyphs contained by a button, including the
 * label and border (if it exists).
 */
void ButtonSetOpacity(Button *button, u8 opacity) {
    for (i32 i = 0; i < ArrayCount(button->label->glyphs); ++i) {
        button->label->glyphs[i]->fg.a = opacity;
        button->label->glyphs[i]->bg.a = opacity;
    }

    for (i32 i = 0; i < ArrayCount(button->panel->glyphs); ++i) {
        button->panel->glyphs[i]->fg.a = opacity;
        button->panel->glyphs[i]->bg.a = opacity;
    }
}