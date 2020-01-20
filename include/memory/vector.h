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
 * \desc The initial capacity of a vector. As long as this value is somewhat
 * small it should not affect performance or memory usage.
 */
#define VECTOR_INITIAL_CAPACITY 4

/**
 * \brief A vector contains size metadata as well as the data themselves.
 *
 * The capacity of a vector is the actual memory set aside for it. Some of the
 * memory within may be unitialised until new data are pushed. The size of the
 * vector is the actual used spaced. The data within the vector are represented
 * as an array of pointers.
 */
typedef struct Vector_s {
    size_t capacity;
    size_t size;
    void **data;
} Vector;

/**
 * \brief Creates an empty vector.
 * \returns Pointer to an empty vector.
 */
Vector *VectorCreate(void);

/**
 * \brief Frees the memory of a vector.
 * \param [out] vec The vector to be freed.
 * \returns Void.
 */
void VectorFree(Vector *vec);

/**
 * \brief Finds the actual used space of a vector.
 * \param [in] vec The vector to find the length of.
 * \returns The length of the vector.
 */
size_t VectorLength(const Vector *vec);

/**
 * \brief Resizes a vector to a given capacity.
 * \param [out] vec The vector to be resized.
 * \param [in] capacity The capacity to resize to.
 * \returns Void.
 */
void VectorResize(Vector *vec, size_t capacity);

/**
 * \brief Pushes an object to the end of the vector.
 * \param [out] vec The vector to push an object to.
 * \param [in] data The data to push.
 * \returns Void.
 */
void VectorPush(Vector *vec, void *data);

/**
 * \brief Puts data into a given position within a vector.
 * \param [out] vec The vector to assign data to.
 * \param [in] index The index to where the data should be assigned.
 * \param [in] data The data to assign.
 * \returns Void.
 */
void VectorSet(Vector *vec, size_t index, void *data);

/**
 * \brief Returns an object at a given index within a vector.
 * \param [in] vec The vector to return data from.
 * \param [in] index The index in the vector to get the data from.
 * \returns The data at a given index.
 */
void *VectorAt(const Vector *vec, size_t index);

/**
 * \brief Returns the data at the front of a vector.
 * \param [in] vec The vector to return data from.
 * \returns The data at the front of a vector.
 */
void *VectorFront(const Vector *vec);

/**
 * \brief Returns the data at the back of a vector.
 * \param [in] vec The vector to return data from.
 * \returns The data at the back of a vector.
 */
void *VectorBack(const Vector *vec);

/**
 * \brief Deletes data at a given index within a vector.
 * \param [out] vec The vector to delete data from.
 * \returns Void.
 */
void VectorDelete(Vector *vec, size_t index);

#endif