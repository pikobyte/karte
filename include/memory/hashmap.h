/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file hashmap.h
 *
 * \brief A hashmap is a data structure which allows the retrieval of data in
 * O(1) complexity. Data are stored as key-value pairs and are addressed via
 * their keys. A hashing function is employed to prevent data from being
 * inserted into the same position in memory multiple times.
 *
 * \author Anthony Mercer
 *
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#include "core/common.h"
#include "core/utils.h"

/**
 * \desc Defines a null pair record for a hashmap.
 */
#define HASHMAP_DELETED_ITEM                                                   \
    (HashRecord) { NULL, NULL }

/**
 * \desc The initial size of a hashmap given as some small prime number.
 */
#define HT_INITIAL_BASE_SIZE 11

/**
 * \desc Two large prime numbers which are required for the hashing function.
 */
#define HT_PRIME_1 101
#define HT_PRIME_2 173

/**
 * \brief Holds a key-value pair.
 *
 * A hashmap record is the data type which forms a key-value pair where the key is
 * a character array and the value can be of any type.
 */
typedef struct HashRecord_s {
    char *key;
    void *value;
} HashRecord;

/**
 * \brief A hashmap with size metadata and a vector of hashmap records.
 *
 * A hashmap contains data regarding its actual size and capacity as well as a
 * set of hashmap records which contain the important data themselves.
 * Additionally a function pointer to a function which frees any of the values
 * within the hashmap is provided. This is stored in a functions structure.
 */
typedef struct Hashmap_s {
    u32 base_size;
    u32 size;
    u32 count;
    HashRecord **records;
    struct {
        void (*free)();
    } functions;
} Hashmap;

/**
 * \brief Creates an empty hashmap record.
 * \returns Pointer to an empty hashmap record.
 */
HashRecord *HashRecordCreate(void);

/**
 * \brief Frees the memory of a hashmap record.
 * \param [out] record The hashmap record to be freed.
 * \returns Void.
 */
void HashRecordFree(HashRecord *record);

/**
 * \brief Creates an empty hashmap.
 * \returns Pointer to an empty hashmap.
 */
Hashmap *HashmapCreate(u32 base_size);

/**
 * \brief Frees the memory of a hashmap and data within if recursive is set.
 * \param [out] hashmap The hashmap to be freed.
 * \param [in] recursive Flag to determined whether data within the hashmap are
 * freed.
 * \returns Void.
 */
void HashmapFree(Hashmap *hashmap, bool recursive);

void HashmapInsert(Hashmap *hashmap, const char *key, void *value);
void *HashmapSearch(const Hashmap *hashmap, const char *key);
void HashmapDelete(Hashmap *hashmap, const char *key);

#endif