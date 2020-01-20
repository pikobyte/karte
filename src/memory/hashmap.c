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
 * \desc The creation of a hashmap record first allocates the required amount of
 * memory and then sets the key and values of that record.
 */
HashRecord *HashRecordCreate(const char *key, void *value) {
    HashRecord *record = Allocate(sizeof(HashRecord));
    record->key = calloc(strlen(key), sizeof(char));
    strcpy(record->key, key);
    record->value = value;
    return record;
}

/**
 * \desc The creation of a hashmap requires a base size represented by a prime
 * number. The actual size is larger than this and is the next prime number up
 * from the base size. The hashmap records are allocated using this new size. A
 * free function is also passed in so that the hashmap can free its data later.
 */
Hashmap *HashmapCreate(size_t base_size, void (*free)()) {
    Hashmap *hashmap = Allocate(sizeof(Hashmap));
    hashmap->base_size = base_size;
    hashmap->size = (size_t)NextPrime((u32)hashmap->base_size);
    hashmap->count = 0;
    hashmap->functions.free = free;
    hashmap->records = Allocate(sizeof(HashRecord *) * hashmap->size);
    return hashmap;
}

/**
 * \desc Simply frees the memory which a hashmap record points to.
 */
void HashRecordFree(HashRecord *record) { Free(record); }

/**
 * \desc A hashmap can be freed via two approaches. The first is to clear the
 * content but preserve the pointers to data within (leaving them dangling).
 * This is useful when resizing a hashmap as we do not want to reallocate the
 * record memory. The second is to recursively free the memory of the records.
 * This only occurs when the recursive flag is set, the current record is valid
 * and that a free function exists for the hashmap.
 */
void HashmapFree(Hashmap *hashmap, bool recursive) {
    for (size_t i = 0; i < (size_t)hashmap->size; ++i) {
        HashRecord *record = hashmap->records[i];
        if (record == NULL || record == &HASHMAP_DELETED_ITEM ||
            !strcmp(record->key, "")) {
            continue;
        }

        if (recursive) {
            if (hashmap->functions.free) {
                (*hashmap->functions.free)(record->value);
            } else {
                Log(LOG_NOTIFY, "No free function was provided for hashmap!");
                Free(record->value);
            }
        }

        Free(record->key);
        HashRecordFree(record);
    }

    Free(hashmap->records);
    Free(hashmap);
}

/**
 * \desc Changes the size of a hashmap by allocating a new one and copying the
 * data from the old to the new. This is done via hashmap inserts. Given that a
 * new hashmap is allocated to accomodate this, it is freed at the end of the
 * function and must have the correct values within it, hence the swaps. Of
 * course, if the new base size is less than the initial base size, the function
 * returns early.
 */
void HashmapResize(Hashmap *hashmap, size_t base_size) {
    if (base_size < HASHMAP_INITIAL_BASE_SIZE) {
        return;
    }

    Hashmap *new_hashmap = HashmapCreate(base_size, hashmap->functions.free);
    for (size_t i = 0; i < hashmap->size; ++i) {
        HashRecord *record = hashmap->records[i];
        if (record != NULL && record != &HASHMAP_DELETED_ITEM) {
            HashmapInsert(new_hashmap, record->key, record->value);
        }
    }

    hashmap->base_size = new_hashmap->base_size;
    hashmap->count = new_hashmap->count;

    const size_t tmp_size = hashmap->size;
    hashmap->size = new_hashmap->size;
    new_hashmap->size = tmp_size;

    HashRecord **tmp_records = hashmap->records;
    hashmap->records = new_hashmap->records;
    new_hashmap->records = tmp_records;

    HashmapFree(new_hashmap, false);
}

/**
 * \desc The insertion of a key-value pair triggers a resize of the hashmap if
 * it exceeds a certain load thus increasing its size to accomodate the new
 * record.
 */
void HashmapInsert(Hashmap *hashmap, const char *key, void *value) {
    const size_t load = hashmap->count / hashmap->size;
    if (load > HASHMAP_LOAD_INCREASE) {
        HashmapResize(hashmap, hashmap->base_size << 1);
    }

    HashRecord *record = HashRecordCreate(key, value);
    u32 index = HashGet(record->key, hashmap->size, 0);
    HashRecord *last_record = hashmap->records[index];

    u32 i = 1;
    while (last_record != NULL && last_record) {
        if (last_record == &HASHMAP_DELETED_ITEM) {
            continue;
        }

        if (strcmp(last_record->key, key) == 0) {
            if (hashmap->functions.free) {
                (*hashmap->functions.free)(last_record->value);
            } else {
                Free(last_record->value);
            }

            Free(last_record->key);
            HashRecordFree(last_record);
            hashmap->records[index] = record;

            return;
        }

        index = HashGet(record->key, hashmap->size, i);
        last_record = hashmap->records[index];

        i++;
    }

    hashmap->records[index] = record;
    hashmap->count++;
}

/**
 * \desc Iterates through the records in hashmap and compares the record key to
 * the provided key. If the keys match, then the associated value is returned.
 * Otherwise the next record is checked, and a null value is returned if the
 * associated value was not obtained.
 */
void *HashmapSearch(const Hashmap *hashmap, const char *key) {
    size_t index = HashGet(key, hashmap->size, 0);
    HashRecord *record = hashmap->records[index];

    i32 i = 1;
    while (record != NULL) {
        if (record != &HASHMAP_DELETED_ITEM) {
            if (strcmp(record->key, key) == 0) {
                return record->value;
            }
        }

        index = HashGet(key, hashmap->size, i);
        record = hashmap->records[index];

        i++;
    }

    Log(LOG_NOTIFY, "No value associated to key %s in hashmap!", key);
    return NULL;
}

void HashmapDelete(Hashmap *hashmap, const char *key) {
    const size_t load = hashmap->count / hashmap->size;
    if (load < HASHMAP_LOAD_DECREASE) {
        HashmapResize(hashmap, hashmap->base_size >> 1);
    }

    i32 index = HashGet(key, hashmap->size, 0);
    HashRecord *record = hashmap->records[index];

    i32 i = 0;
    while (record != NULL) {
        if (record == &HASHMAP_DELETED_ITEM) {
            continue;
        }

        if (strcmp(record->key, key) == 0) {
            if (hashmap->functions.free) {
                (*hashmap->functions.free)(record->value);
            } else {
                Free(record->value);
            }

            free(record->key);
            HashRecordFree(record);
            hashmap->records[index] = &HASHMAP_DELETED_ITEM;
            hashmap->count--;

            return;
        }

        index = HashGet(key, hashmap->size, i);
        record = hashmap->records[index];

        i++;
    }

    Log(LOG_NOTIFY, "Could not delete record with key %s from hashmap!", key);
}

/**
 * \desc A hash function takes a string input and generates a (typically) unique
 * hash for that string. This involves raising a prime to a large power and then
 * taking the modulus of it by some other value. This keeps the hash within
 * reasonable values and so a very large amount of empty memory is not allocated
 * for each hashmap.
 */
i32 HashFunction(const char *str, u32 prime, size_t num_rec) {
    i64 hash = 0;
    const size_t length = strlen(str);
    for (size_t i = 0; i < length; ++i) {
        const f64 exponent = (f64)(length - (i + 1));
        hash += (i64)pow(prime, exponent) * str[i];
        hash = hash % num_rec;
    }
    return (i32)hash;
}

/**
 * \desc This function generates two hashes (based off of different prime
 * numbers) and uses them to obtain an index within a hashmap for that key. The
 * attempt count is tracked to mitigate "double-booked" indices.
 */
i32 HashGet(const char *str, size_t num_rec, i32 attempt) {
    const i32 hash_a = HashFunction(str, HASHMAP_PRIME_1, num_rec);
    const i32 hash_b = HashFunction(str, HASHMAP_PRIME_2, num_rec);

    return (hash_a + attempt * (hash_b == 0 ? 1 : hash_b)) % num_rec;
}