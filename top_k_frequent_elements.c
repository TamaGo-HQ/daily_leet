/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define TABLE_SIZE 1000  // Adjust as needed

// Hashmap entry
typedef struct Entry {
    int key;             // integer key
    int value;           // frequency (or any integer value)
    struct Entry* next;  // pointer to handle collisions
} Entry;

// Hashmap
typedef struct {
    Entry* table[TABLE_SIZE];
} HashMap;

// Hash function
unsigned int hash(int key) {
    return abs(key) % TABLE_SIZE;
}

// Create a new hashmap
HashMap* create_hashmap() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
    return map;
}

// Insert or update frequency
void hashmap_put(HashMap* map, int key) {
    unsigned int idx = hash(key);
    Entry* curr = map->table[idx];

    // Search for existing key
    while (curr != NULL) {
        if (curr->key == key) {
            curr->value++; // increment frequency
            return;
        }
        curr = curr->next;
    }

    // If key not found, create new entry
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = key;
    new_entry->value = 1;  // first occurrence
    new_entry->next = map->table[idx];
    map->table[idx] = new_entry;
}

// Get frequency of a key
int hashmap_get(HashMap* map, int key) {
    unsigned int idx = hash(key);
    Entry* curr = map->table[idx];

    while (curr != NULL) {
        if (curr->key == key)
            return curr->value;
        curr = curr->next;
    }
    return 0; // not found
}

void free_hashmap(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* curr = map->table[i];
        while (curr != NULL) {
            Entry* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(map);
}

typedef struct {
    int key;
    int freq;
} Pair;

typedef struct {
    Pair* data;
    int size;
    int capacity;
}heap;

heap* create_heap(int capacity) {
    heap* h = malloc(sizeof(heap));
    h->data = malloc(capacity * sizeof(Pair));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap(Pair* a, Pair* b) {
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(heap* h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (h->data[parent].freq <= h->data[idx].freq)
            break;
        swap(&h->data[parent], &h->data[idx]);
        idx = parent;
    }
}

void heapify_down(heap* h, int idx) {
    while (1) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < h->size && h->data[left].freq < h->data[smallest].freq)
            smallest = left;
        if (right < h->size && h->data[right].freq < h->data[smallest].freq)
            smallest = right;

        if (smallest == idx) break;
        swap(&h->data[smallest], &h->data[idx]);
        idx = smallest;
    }
}

void heap_push(heap* h, Pair val) {
    if (h->size < h->capacity) {
        h->data[h->size] = val;
        heapify_up(h, h->size);
        h->size++;
    } else if (val.freq > h->data[0].freq) {
        // replace root (smallest) and heapify
        h->data[0] = val;
        heapify_down(h, 0);
    }
}

void free_heap(heap* h) {
    free(h->data);
    free(h);
}
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    
    HashMap* map = create_hashmap();

    // Count frequencies
    for (int i = 0; i < numsSize; i++) {
        hashmap_put(map, nums[i]);
    }

    heap* heap_k = create_heap(k);
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* curr = map->table[i];
        while (curr != NULL) {
            Pair p = { curr->key, curr->value };
            heap_push(heap_k, p);
            curr = curr->next;
        }
    }
    
    int* result = (int*) malloc (k*sizeof(int));
    for (int i = 0; i < heap_k->size; i++) {
        result[i] = heap_k->data[i].key;
    }
    *returnSize = k; 

    free_heap(heap_k);
    free_hashmap(map);
    return result;
}