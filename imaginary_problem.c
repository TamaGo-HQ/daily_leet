/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define TABLE_SIZE 10007  // big prime number for hashing

// Node to store an index
typedef struct idx{
    int idx;
    struct idx* next;
}idx_t;

// Hashmap entry
typedef struct element {
    double key;   // encoded key
    int count;          // number of indices
    idx_t* idx_list;        // linked list of indices
    struct element* next; // for collision chaining
} element_t;

typedef struct {
    element_t* table[TABLE_SIZE];
} hashmap_t;

// Hash a float into an integer
unsigned int hash_float(double key) {
    // Scale the float to preserve some precision
    long int_repr = (long)(key * 1000000); // multiply by 1e6
    // Simple modulo hash
    return (unsigned int)(int_repr % TABLE_SIZE);
}

// Create a new hashmap
hashmap_t* create_hashmap() {
    hashmap_t* map = (hashmap_t*)malloc(sizeof(hashmap_t));
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
    return map;
}

void hashmap_put(hashmap_t* map, double key, int str_idx) {
    unsigned int hash_idx = hash_float(key);
    element_t* cur = map->table[hash_idx];

    // Look for existing key
    while (cur) {
        if (cur->key == key) break;
        cur = cur->next;
    }

    if (!cur) {
        // Create new hashmap entry
        cur = (element_t*)malloc(sizeof(element_t));
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

// Map letters to numbers: a=1, b=2, ..., z=26
int letter_to_value(char c) {
    c = tolower(c);
    if (c < 'a' || c > 'z') return 1; // default value for non-letters
    return c - 'a' + 1;
}

// Encode word: 676 / first * second / third * fourth ...
double encode_word_alt(const char *word) {
    if (!word || word[0] == '\0') return 0.0;

    double result = 676.0;
    int divide_next = 1; // start with division

    for (int i = 0; word[i] != '\0'; i++) {
        int val = letter_to_value(word[i]);
        if (val == 0) val = 1; // avoid division by zero

        if (divide_next)
            result /= val;
        else
            result *= val;

        divide_next = !divide_next; // alternate
    }

    return result;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    hashmap_t* map = create_hashmap();
    //create hashmap where the key is the encoded word, anagrams inevetibly have the same key
    for(int i = 0; i < strsSize; i++){
        double key = encode_word_alt(strs[i]);
        hashmap_put(map, key, i);
    }
    // Allocate space for max possible groups
    char*** result = malloc(sizeof(char**) * strsSize);
    *returnColumnSizes = malloc(sizeof(int) * strsSize);
    *returnSize = 0;

    // Traverse table and build result groups
    for (int i = 0; i < TABLE_SIZE; i++) {
        element_t* cur = map->table[i];
        while (cur) {

            // Allocate group
            (*returnColumnSizes)[*returnSize] = cur->count;
            result[*returnSize] = malloc(sizeof(char*) * cur->count);

            int k = 0;
            for (idx_t* n = cur->idx_list; n; n = n->next) {
                result[*returnSize][k++] = strs[n->idx];
            }

            (*returnSize)++;
            cur = cur->next;
        }
    }

    return result;
}
