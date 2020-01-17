/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file selector.h
 *
 * \brief A selector is a widget which allwos the user to choose a glyph or a
 * colour. The glyphs as part of the selector are immutable, in contrast to a
 * canvas.
 *
 * \author Anthony Mercer
 *
 */

#ifndef SELECTOR_H
#define SELECTOR_H

#include "color.h"
#include "glyph.h"
#include "input.h"
#include "utils.h"

/**
 * \brief Describes the type of selector.
 *
 * A selector can be used to choose glyph properties, whether it be foreground
 * colour, background colour or the glyph index. This enumeration acts as a bit
 * field.
 */
typedef enum SelectorType_e {
    SELECTOR_NONE = 0,
    SELECTOR_INDEX = 1 << 0,
    SELECTOR_FOREGROUND = 1 << 1,
    SELECTOR_BACKGROUND = 1 << 2
} SelectorType;

typedef struct Selector_s {
    Glyph **glyphs;    /**< The glyphs representing the selector. */
    Glyph *cur_glyph;  /**< Currently selected glyph. */
    SelectorType type; /**< The type of selection that will be utilised. */
    SDL_Rect rect;     /**< Dimensions of the selector in glyph dimensions. */
} Selector;

/**
 * \brief Create a selector with initial glyph and physical dimensions.
 * \param [in] rect The dimensions of the selector in glyph units.
 * \param [in] type The type of selector the created one should be.
 * \returns Pointer to a selector object.
 */
Selector *SelectorCreate(SDL_Rect rect, SelectorType type);

/**
 * \brief Frees the selector memory.
 * \param [in, out] selector The selector to be freed.
 * \returns Void.
 */
void SelectorFree(Selector *selector);

/**
 * \brief Deals with the input of a selector based on its type.
 * \param [in, out] selector The selector to test input from.
 * \param [in] input An input handler.
 * \returns Void.
 */
void SelectorHandleInput(Selector *selector, const Input *input);

/**
 * \brief Updates a selector.
 * \param [in, out] selector The selector to be updated.
 * \param [in, out] cur_glyph A current glyph to be changed based on the
 * selector type. \returns Void.
 */
void SelectorUpdate(Selector *selector, Glyph *cur_glyph);

/**
 * \brief Renders a selector.
 * \param [in] selector Selector to render.
 * \param [in] wind Window to render to.
 * \param [in] tex Texture to render from.
 * \returns Void.
 */
void SelectorRender(const Selector *selector, const Window *wind,
                    const Texture *tex);

/**
 * \brief Sets the current glyph based on a type of selector.
 * \param [in, out] selector Selector to set the current glyph of.
 * \param [in] glyph Glyph to take the properties from.
 * \param [in] type The type of selector.
 * \returns Void.
 */
void SelectorSetCurrentGlyph(Selector *selector, const Glyph *glyph,
                             SelectorType type);

/**
 * \brief Assign glyph properties based on a selector's current glyph.
 * \param [in] selector Selector to get the current glyph from.
 * \param [in, out] glyph Glyph to set the properties to.
 * \returns Void.
 */
void SelectorGetCurrentGlyph(const Selector *selector, Glyph *glyph);

#endif