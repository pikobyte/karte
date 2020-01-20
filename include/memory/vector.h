/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file vector.c
 *
 * \brief A vector is a growable form of array which can contain any type. The
 * size of a vector doubles each time it is filled to capacity.
 *
 * \author Anthony Mercer
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "core/common.h"
#include "core/utils.h"

/**
 * \desc Given a vector, it is checked for validity, and if it is, is freed.
 */
#define VectorFree(vec) (vec ? free(VectorPtr(vec)), 0 : 0)

/**
 * \desc Pushes a value to a vector. If the vector needs to grow given this
 * single item push, it does so. Otherwise, the used element count is
 * incremented, and that index is set to the desired pointer.
 */
#define VectorPush(vec, v) (VectorQueryGrow(vec, 1), vec[VectorUsed(vec)++] = v)

/**
 * \desc Returns the number of used elements in a vector if it is valid.
 */
#define VectorCount(vec) (vec ? VectorUsed(vec) : 0)

/**
 * \desc Returns the last used member within a vector.
 */
#define VectorLast(vec) (vec ? vec[VectorUsed(vec) - 1] : 0)

/**
 * \desc Removes the first member of a vector and shrinks the vector to
 * compensate.
 */
#define VectorPopFront(vec) (vec = VectorShrink(vec, 0, sizeof(*vec)))

/**
 * \desc Removes the last member of a vector and shrinks the vector to
 * compensate.
 */
#define VectorPopBack(vec)                                                     \
    (vec = VectorShrink(vec, vecayLast(vec), sizeof(*vec)))

/**
 * \desc Returns the pointer to a vector data. The header includes two 32-bit
 * integers, the first holding the vector size, the second the number of used
 * elements.
 */
#define VectorPtr(vec) ((i32 *)(vec)-2)

/**
 * \desc Returns the size of the vector which is stored in the first part of the
 * vector header.
 */
#define VectorSize(vec) VectorPtr(vec)[0]

/**
 * \desc Returns the used members of a vector which is stored in the second part
 * of the vector header.
 */
#define VectorUsed(vec) VectorPtr(vec)[1]

/**
 * \desc Checks if the vector size is zero or if the current used elements plus
 * the desired elements is larger than the vector size.
 */
#define VectorReqGrow(vec, n)                                                  \
    (vec == 0 || VectorUsed(vec) + n >= VectorSize(vec))

/**
 * \desc Queries the vector to see if the requirement to grow is true. If it is,
 * then the size is increased.
 */
#define VectorQueryGrow(vec, n) (VectorReqGrow(vec, n) ? VectorGrow(vec, n) : 0)

/**
 * \desc Sets a vector size to that required to fit in required elements.
 */
#define VectorGrow(vec, n) (vec = VectorGrowBy(vec, n, sizeof(*vec)))

/**
 * \brief Grows a vector by increasing its size.
 * \param [in] vec Vector to increase the size of.
 * \param [in] n The number of elements to grow the vector by.
 * \param [in] size The size of object which populates the vector.
 * \returns The reallocated vector, with a pointer to the data i.e. after the
 * header.
 */
void *VectorGrowBy(const void *vec, i32 n, i32 size);

#endif