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
 * \desc The growth of an vector involves the increasing of its size and
 * consequent reallocation. If reallocation fails, an error is issued and only
 * vector header is allocated. The first calculation is the double current size,
 * which is zero if the vector is NULL. The minimum required memory is the
 * current usage plus the number of required elements. A decision is then made:
 * whether the double size is greater than that required, the smaller of the two
 * is the actual required. The total space required for reallocation is the
 * number of actual required elements, multiplied by the size of object within
 * the vector, plus the 2 32-bit integer header. If the reallocated memory not
 * given, an error is logged and only vector header memory is allocated.
 * Otherwise, if the vector is currently NULL, the number of used elements is
 * set to zero. The size of the vector (number of indices) is set in the header,
 * and the pointer to the new memory data (skipping header) is returned.
 */
void *VectorGrowBy(const void *arr, i32 n, i32 size) {
    const i32 dbl_cur = arr ? 2 * VectorSize(arr) : 0;
    const i32 min_req = VectorCount(arr) + n;
    const i32 act_req = dbl_cur > min_req ? dbl_cur : min_req;
    const i32 tot_req = size * act_req + sizeof(i32) * 2;

    i32 *ptr = (i32 *)realloc(arr ? VectorPtr(arr) : 0, tot_req);

    if (ptr) {
        if (!arr) {
            ptr[1] = 0;
        }
        ptr[0] = act_req;
        return ptr + 2;
    } else {
        Log(LOG_ERROR, "Could not allocate Vector of size %i!", tot_req);
        return (void *)(2 * sizeof(i32));
    }
}