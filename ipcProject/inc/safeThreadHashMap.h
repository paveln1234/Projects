#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stddef.h>  /* size_t */

/**
 *  @file safeThreadHashMap.h
 *  @brief Thread Safe Generic Hash map of key-value pairs implemented with separate chaining using linked lists.
 *
 *  @details  The hash map (sometimes called dictionary or associative array)
 *  is a set of distinct keys (or indexes) mapped (or associated) to values.
 *  size of allocated table will be the nearest prime number greater than requested capacity.
 *  Lists used for chaining will be allocated eagerly.
 *
 *  @author Pavel Korolin
 *
 *  @bug rehash still no thread safe and run it will colept the system.
 */


typedef struct STHashMap_t STHashMap_t;

typedef enum Map_Result {
	MAP_SUCCESS = 0,
	MAP_UNINITIALIZED_ERROR, 		/**< Uninitialized map error 	*/
	MAP_KEY_NULL_ERROR, 			/**< Key was null 				*/
	MAP_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 		*/
	MAP_KEY_NOT_FOUND_ERROR, 		/**< Key not found 				*/
	MAP_ALLOCATION_ERROR 			/**< Allocation error 	 		*/
} Map_Result;


typedef size_t (*HashFunction)(const void* _key);
typedef int (*EqualityFunction)(const void* _firstKey, const void* _secondKey);
typedef size_t(*KeyValueActionFunction)(const void* _key, void* _value, void* _context);



/**
 * @brief Create a new hash map with given capcity and key characteristics.
 * @param[in] _capacity - Expected max capacity
 * 						  shall be rounded to nearest larger prime number.
 * @param[in] _hashFunc - hashing function for keys
 * @param[in] _keysEqualFunc - equality check function for keys.
 * @return newly created map or null on failure
 */
STHashMap_t* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);


/**
 * @brief destroy hash map and set *_map to null
 * @param[in] _map : map to be destroyed
 * @param[optional] _keyDestroy : pointer to function to destroy keys
 * @param[optional] _valDestroy : pointer to function to destroy values
 * @details optionally destroy all keys and values using user provided functions
 */
void HashMap_Destroy(STHashMap_t** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));


/**
 * @brief Adjust map capacity and rehash all key/value pairs
 * @param[in] _map - exisiting map
 * @param[in] _newCapacity - new capacity shall be rounded to nearest larger prime number.
 * @return MAP_SUCCESS or MAP_ALLOCATION_ERROR
 */
Map_Result HashMap_Rehash(STHashMap_t*_map, size_t newCapacity);


/**
 * @brief Insert a key-value pair into the hash map.
 * @param[in] _map - Hash map to insert to, must be initialized
 * @param[in] _key - key to serve as index
 * @param[in] _value - the value to associate with the key
 * @return Map_Result
 * @warning key must be unique and destinct value pointer is not NULL
 */
Map_Result HashMap_Insert(STHashMap_t* _map, const void* _key, const void* _value);


/**
 * @brief Remove a key-value pair from the hash map.
 * @param[in] _map - Hash map to remove pair from, must be initialized
 * @param[in] _searchKey - key to to search for in the map
 * @param[out] _pKey - pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out] _pValue - pointer to variable that will get the value stored in the map corresponding to foind key
 * @return Map_Result
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Remove(STHashMap_t* _map, const void* _searchKey, void** _pKey, void** _pValue);


/**
 * @brief Find a value by key
 * @param[in] _map - Hash map to use, must be initialized
 * @param[in] _searchKey - key to serve as index for search
 * @param[in] KeyValueActionFunction _action - optional User provided function pointer to be invoked for _ppValue
 * @param[out] _pValue - pointer to variable that will get the value assoiciated with the search key.
 * @param[in] void* _context for action function.
 * @return Map_Result
 * @warning key must be unique and destinct
 * @warning if action function given value will not return to the user;
 */
Map_Result HashMap_Find( STHashMap_t* _map, const void* _searchKey, KeyValueActionFunction _action ,void** _ppValue,void* _context);

/**
 * @brief Get number of key-value pairs inserted into the hash map
 * @warning complexity can be O(?)
 * @warning in case of NULL map return 0;
 */
size_t HashMap_Size( STHashMap_t* _map);


/**
 * This method is optional in the homework
 * @brief Iterate over all key-value pairs in the map and call a function for each pair
 * The user provided KeyValueActionFunction will be called for each element.
 * Iteration will stop if the called function returns a zero for a given pair
 *
 * @param[in] _map - Hash map to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided function pointer to be invoked for each element
 * @returns number of times the user functions was invoked
 */
size_t HashMap_ForEach(const STHashMap_t* _map, KeyValueActionFunction _action, void* _context);


#ifndef NDEBUG

typedef struct Map_Stats {
	size_t numberOfBuckets;    /* empty + not empty buckets */
	size_t numberOfNonEmptyBuckets;     /* none empty chains (having non zero length) */
	size_t maxChainLength;     /* length of longest chain */
	size_t averageChainLength; /* average length of none empty chains */
}Map_Stats;

Map_Stats* HashMap_GetStatistics(const STHashMap_t* _map);

#endif /* NDEBUG */


#endif /* __HASHMAP_H__ */





