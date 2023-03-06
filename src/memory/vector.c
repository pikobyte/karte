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

#include "memory/vector.h"

/**
 * \desc The creation of a vector involves setting the initial capacity and
 * allocating the actual memory correspondant to that capacity. Initially,
 * vectors have no content.
 */
[[nodiscard]] Vector* VectorCreate(void)
{
    Vector* vec = Allocate(sizeof(Vector));
    vec->capacity = VECTOR_INITIAL_CAPACITY;
    vec->size = 0;
    vec->data = Allocate(sizeof(void*) * vec->capacity);
    return vec;
}

/**
 * \desc Freeing a vector simply involves freeing the data within.
 */
void VectorFree(Vector* vec) { Free(vec->data); }

/**
 * \desc The length of a vector is the number of actual objects within it. This
 * function clears the confusion between size and capacity.
 */
[[nodiscard]] size_t VectorLength(const Vector* vec) { return vec->size; }

/**
 * \desc Resizes a vector provided the capacity is at least unity. The vector
 * data is reallocated to the new capacity and the data are set accordingly.
 */
void VectorResize(Vector* vec, size_t capacity)
{
    if (capacity < 1)
    {
        return;
    }

    void** data = realloc(vec->data, sizeof(void*) * capacity);
    if (!data)
    {
        Log(LOG_ERROR, "Could not resize vector to %u!", capacity);
        return;
    }

    vec->data = data;
    vec->capacity = capacity;
}

/**
 * \desc Performs a check as to whether the vector capacity should be expanded
 * and then appends data to the end of the current set. The vector size is also
 * incremented. If a resize is triggered, the vector capacity is doubled.
 */
void VectorPush(Vector* vec, void* data)
{
    if (vec->capacity == vec->size)
    {
        VectorResize(vec, vec->capacity << 1);
    }

    vec->data[vec->size++] = data;
}

/**
 * \desc Performs a check as to whether the index provided is within the vector
 * bounds. If it is, the data at that index are set based on the given input.
 */
void VectorSet(Vector* vec, size_t index, void* data)
{
    if (index > vec->size - 1)
    {
        Log(LOG_ERROR, "VectorSet: index %u out of bounds!", index);
        return;
    }

    vec->data[index] = data;
}

/**
 * \desc Performs a check as to whether the index provided is within the vector
 * bounds. If it is, the data at that index are returned.
 */
void* VectorAt(const Vector* vec, size_t index)
{
    if (index > vec->size - 1)
    {
        Log(LOG_ERROR, "VectorAt: index %u out of bounds!", index);
        return NULL;
    }

    return vec->data[index];
}

/**
 * \desc Performs a check as to whether the data at the front of the vector are
 * valid and returns it if it is.
 */
void* VectorFront(const Vector* vec)
{
    void* data = vec->data[0];
    if (!data)
    {
        Log(LOG_ERROR, "VectorFront: no data at front of vector!");
        return NULL;
    }
    return data;
}

/**
 * \desc Performs a check as to whether the data at the back of the vector are
 * valid and returns it if it is.
 */
void* VectorBack(const Vector* vec)
{
    void* data = vec->data[vec->size - 1];
    if (!data)
    {
        Log(LOG_ERROR, "VectorBack: no data at back of vector!");
        return NULL;
    }
    return data;
}

/**
 * \desc Performs a check as to whether the index provided is within the vector
 * bounds. If it is, the data at that position is set to null. The data in the
 * vector are then compacted and the size decremented. If the new size of the
 * vector is a quarter of its capacity, it halves the capacity of the vector.
 */
void VectorDelete(Vector* vec, size_t index)
{
    if (index > vec->size - 1)
    {
        Log(LOG_ERROR, "VectorDelete: index %u out of bounds!", index);
        return;
    }

    vec->data[index] = NULL;

    for (size_t i = 0; i < vec->size - 1; ++i)
    {
        vec->data[i] = vec->data[i + 1];
        vec->data[i + 1] = NULL;
    }

    vec->size--;

    if (vec->size > 0 && vec->size <= vec->capacity / 4)
    {
        VectorResize(vec, vec->capacity >> 1);
    }
}
