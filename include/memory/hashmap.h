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
#define HASHMAP_INITIAL_BASE_SIZE 11

/**
 * \desc Two large prime numbers which are required for the hashing function.
 */
#define HASHMAP_PRIME_1 101
#define HASHMAP_PRIME_2 173

/**
 * \desc Percentage based limits to determine whether a hashmap should be
 * resized.
 */
#define HASHMAP_LOAD_INCREASE 70
#define HASHMAP_LOAD_DECREASE 10

/**
 * \desc A function pointer which is used for freeing hashmap data.
 */
#define FreeFunction (void (*free)())

/**
 * \brief Holds a key-value pair.
 *
 * A hashmap record is the data type which forms a key-value pair where the key
 * is a character array and the value can be of any type.
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
    size_t base_size;
    size_t size;
    size_t count;
    HashRecord **records;
    struct {
        void (*free)();
    } functions;
} Hashmap;

/**
 * \brief Creates a hashmap record with a key and a value.
 * \param [in] key The key string for the record.
 * \param [in] value The actual data associated with that key.
 * \returns Pointer to a hashmap record.
 */
HashRecord *HashRecordCreate(const char *key, const void *value);

/**
 * \brief Frees the memory of a hashmap record.
 * \param [out] record The hashmap record to be freed.
 * \returns Void.
 */
void HashRecordFree(HashRecord *record);

/**
 * \brief Creates an empty hashmap.
 * \param [in] base_size The initial size of the hashmap.
 * \pararm [in] free A function pointer to a memory free function.
 * \returns Pointer to an empty hashmap.
 */
Hashmap *HashmapCreate(size_t base_size, void (*free)());

/**
 * \brief Frees the memory of a hashmap and data within if recursive is set.
 * \param [out] hashmap The hashmap to be freed.
 * \param [in] recursive Flag to determined whether data within the hashmap are
 * freed.
 * \returns Void.
 */
void HashmapFree(Hashmap *hashmap, bool recursive);

/**
 * \brief Resizes a hashmap based on a newly given base size.
 * \param [out] hashmap The hashmap to resize.
 * \param [in] base_size A new base size to increase to.
 * \returns Void.
 */
void HashmapResize(Hashmap *hashmap, size_t base_size);

/**
 * \brief Inserts a key-value pair into a hashmap.
 * \param [out] hashmap The hashmap have a key-value pair inserted into.
 * \param [in] key A string key used to identify the value.
 * \param [in] value A pointer to some data to add to the hashmap.
 * \returns Void.
 */
void HashmapInsert(Hashmap *hashmap, const char *key, void *value);

/**
 * \brief Searches through a hashmap and returns a value if it is associated
 * with the provided key.
 * \param [in] hashmap The hashmap to search.
 * \param [in] key The key used for the search.
 * \returns A value (if found) associated with the given key.
 */
void *HashmapSearch(const Hashmap *hashmap, const char *key);

/**
 * \brief Deletes a record within a hashmap if the key is found.
 * \param [in] hashmap The hashmap to delete a record from.
 * \param [in] key The key of the record to delete.
 * \returns Void.
 */
void HashmapDelete(Hashmap *hashmap, const char *key);

/**
 * \brief Generates a unique hash from string input.
 * \param [in] str The string to generate a hash for.
 * \param [in] prime Any given prime number.
 * \param [in] num_rec The number of records within a hashmap.
 * \returns Void.
 */
i32 HashFunction(const char *str, u32 prime, size_t num_rec);

/**
 * \brief Retrieves an index for a hashmap based on a given key.
 * \param [in] str The key used to get the index
 * \param [in] num_rec The number of records within a hashmap
 * \param [in] attempt Current attempt of the index find.
 * \returns The index of the key.
 */
i32 HashGet(const char *str, size_t num_rec, i32 attempt);

#endif