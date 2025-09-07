/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct word{
    int key;
    float value;
    int idx;
    struct word* next;
}word_t;

typedef struct hashmap{
    word_t* map;
}hashmap_t;

// Hash a float into an integer
unsigned int hash_float(float key, unsigned int table_size) {
    // Scale the float to preserve some precision
    long int_repr = (long)(key * 1000000); // multiply by 1e6
    // Simple modulo hash
    return (unsigned int)(int_repr % table_size);
}

// Create a new hashmap
HashMap* create_hashmap() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
    return map;
}

void put_hashmap(HashMap_t* map, Element_t* element){
    unsigned int idx = hash(element->key);
    Element_t* cur = map->table[idx];
    if (cur == NULL){
        map->table[idx] = element;
    } else {
    // chaining: insert at the beginning
    element->next = cur;
    map->table[idx] = element;
    }
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

}
