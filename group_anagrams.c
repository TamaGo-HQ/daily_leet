#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TABLE_SIZE 10007  // big prime number for hashing

// Node to store an index
typedef struct idx {
    int idx;
    struct idx* next;
} idx_t;

// Hashmap element
typedef struct element {
    long long key;       // encoded key as integer
    int count;           // number of indices
    idx_t* idx_list;     // linked list of indices
    struct element* next; // for collision chaining
} element_t;

// Hashmap
typedef struct {
    element_t* table[TABLE_SIZE];
} hashmap_t;

// Log-prime map (we scale to integer)
double prime_log_map[26];

// Initialize log-prime map
void init_prime_log_map() {
    int primes[26] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101
    };
    for (int i = 0; i < 26; i++)
        prime_log_map[i] = log(primes[i]);
}

// Encode word into a long long key using log-prime scaled to int
long long encode_word_log_int(const char* word) {
    long long sum = 0;
    for (int i = 0; word[i]; i++) {
        char c = word[i] | 32; // tolower
        if (c >= 'a' && c <= 'z')
            sum += (long long)(prime_log_map[c - 'a'] * 1e9); // scale to integer
    }
    return sum;
}

// Hash a long long into table index
unsigned int hash_long_long(long long key) {
    long long mod = key % TABLE_SIZE;
    if (mod < 0) mod += TABLE_SIZE;
    return (unsigned int)mod;
}

// Create a new hashmap
hashmap_t* create_hashmap() {
    hashmap_t* map = malloc(sizeof(hashmap_t));
    for (int i = 0; i < TABLE_SIZE; i++)
        map->table[i] = NULL;
    return map;
}

// Insert into hashmap
void hashmap_put(hashmap_t* map, long long key, int str_idx) {
    unsigned int hash_idx = hash_long_long(key);
    element_t* cur = map->table[hash_idx];

    // Look for existing key
    while (cur) {
        if (cur->key == key) break; // exact integer comparison
        cur = cur->next;
    }

    if (!cur) {
        cur = malloc(sizeof(element_t));
        cur->key = key;
        cur->count = 0;
        cur->idx_list = NULL;
        cur->next = map->table[hash_idx];
        map->table[hash_idx] = cur;
    }

    idx_t* new_idx = malloc(sizeof(idx_t));
    new_idx->idx = str_idx;
    new_idx->next = cur->idx_list;
    cur->idx_list = new_idx;
    cur->count++;
}

// Group anagrams
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    init_prime_log_map(); // initialize prime logs
    hashmap_t* map = create_hashmap();

    // Insert all words into hashmap
    for (int i = 0; i < strsSize; i++) {
        long long key = encode_word_log_int(strs[i]);
        hashmap_put(map, key, i);
    }

    // Allocate maximum possible groups
    char*** result = malloc(sizeof(char**) * strsSize);
    *returnColumnSizes = malloc(sizeof(int) * strsSize);
    *returnSize = 0;

    // Build groups from hashmap
    for (int i = 0; i < TABLE_SIZE; i++) {
        element_t* cur = map->table[i];
        while (cur) {
            (*returnColumnSizes)[*returnSize] = cur->count;
            result[*returnSize] = malloc(sizeof(char*) * cur->count);

            int k = 0;
            for (idx_t* n = cur->idx_list; n; n = n->next)
                result[*returnSize][k++] = strs[n->idx];

            (*returnSize)++;
            cur = cur->next;
        }
    }

    return result;
}
