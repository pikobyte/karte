/* =============================================================================
 *   Karte
 * ========================================================================== */

/**
 * \file hashmap.c
 *
 * \brief A hashmap is a data structure which allows the retrieval of data in
 * O(1) complexity. Data are stored as key-value pairs and are addressed via
 * their keys. A hashing function is employed to prevent data from being
 * inserted into the same position in memory multiple times.
 *
 * \author Anthony Mercer
 *
 */

#include "memory/hashmap.h"

/**
 * \desc The creation of hashmap record first allocates the required amount of
 * memory and then sets the key and values of that record.
 */
HashRecord *HashRecordCreate(const char *key, void *val) {
  HashRecord *record = Allocate(sizeof(HashRecord));
  strcpy(record->key, key);
  record->value = val;
  return record;
}

/**
 * \desc The creation of hashmap requires a base size represented by a prime
 * number. The actual size is larger than this and is the next prime number up
 * from the base size. The hashmap records are allocated using this new size.
 */
Hashmap *HashmapCreate(u32 base_size) {
    Hashmap *hashmap = Allocate(sizeof(Hashmap));
    hashmap->base_size = base_size;
    hashmap->size = NextPrime(hashmap->base_size);
    hashmap->count = 0;
    hashmap->records = Allocate(sizeof(HashRecord *) * hashmap->size);
    return hashmap;
}

/**
 * \desc Simply frees the memory which a hashmap record points to.
 */
void HashRecordFree(HashRecord *record) {
    Free(record);
}

/**
 * \desc A hashmap can be freed via two approaches. The first is to clear the
 * content but preserve the pointers to data within (leaving them dangling).
 * This is useful when resizing a hashmap as we do not want to reallocate the
 * record memory. The second is to recursively free the memory of the records.
 * This only occurs when the recursive flag is set, the current record is valid
 * and that a free function exists for the hashmap.
 */
void HashmapFree(Hashmap *hashmap, bool recursive) {
for (i32 i = 0; i < hashmap->size; ++i) {
    HashRecord *record = hashmap->records[i];
    if (record != NULL && record != &HASHMAP_DELETED_ITEM) {
      if (recursive) {
        if (hashmap->functions.free) {
          (*hashmap->functions.free)(record->value);
        } else {
          Free(record->value);
        }
      }
      Free(record->key);
      HashRecordFree(record);
    }
  }
  
  Free(hashmap->records);
  Free(hashmap);
}