/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */


#define TABLE_SIZE 2001  // Adjust as needed

// Hashmap entry
typedef struct Entry {
    int value;           // frequency (or any integer value)
    struct Entry* next;  // pointer to handle collisions
} Entry;

// Hashmap
typedef struct {
    Entry* table[TABLE_SIZE];
} hashMap;

// Create a new hashmap
hashMap* create_hashmap() {
    hashMap* map = (hashMap*)malloc(sizeof(hashMap));
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
    return map;
}

// Insert or update frequency
void hashmap_put(hashMap* map, int value, int idx) {;
    Entry* cur = map->table[idx];
    Entry* prev = NULL;

    // Search for existing key
    while (cur != NULL) {
        printf("there a guest here! it's %d\n", cur->value);
        prev = cur;
        cur = cur->next;
    }

    // Create new entry
    Entry* newEntry = malloc(sizeof(Entry));
    newEntry->value = value;
    newEntry->next = NULL;

    // Insert it
    if (prev == NULL) {
        // bucket was empty
        map->table[idx] = newEntry;
    } else {
        // append to existing chain
        prev->next = newEntry;
    }
}

void insert_order(struct TreeNode* root, int floor, hashMap* map, int* returnSize, int** returnColumnSizes){
    if(root == NULL){
        return;
    }
    
    hashmap_put(map, root->val, floor);
    (*returnColumnSizes)[floor]++;
    floor++;
    if(floor > *returnSize){ *returnSize = floor;}

    insert_order(root->left, floor, map, returnSize, returnColumnSizes);
    insert_order(root->right, floor, map, returnSize, returnColumnSizes);
}
// Function to print the hash map
void print_hashmap(const hashMap *map) {
    if (map == NULL) {
        printf("Hash map is NULL.\n");
        return;
    }

    printf("Hash Map Contents:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {

        printf("Bucket %d: ", i);
        Entry *current = map->table[i];
        if (current == NULL) {
            printf("Empty\n");
        } else {
            while (current != NULL) {
                printf("(%d)", current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

int** convert_hash_to_2Darray(hashMap* map, int size, int* columnSizes){
    if(size == 0){return NULL;}

    int** result = malloc(size * sizeof(int*));
    int floor = 0;
    //we got on the right floor
    while(columnSizes[floor] != 0){
        result[floor] = malloc(columnSizes[floor] * sizeof(int));
        int i = 0;
        //fill the rooms
        Entry *cur = map->table[floor];
        while (cur != NULL){
            result[floor][i] = cur->value;
            cur = cur->next;
            i++;
        }
        floor++;
    }
    return result;
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    //allocate array, worst case: binary tree is a pseudo linked list
    *returnColumnSizes = calloc(TABLE_SIZE,sizeof(int));
    *returnSize = 0;
    hashMap* map = create_hashmap();

    insert_order(root, 0, map, returnSize, returnColumnSizes);
    printf("this is the size %d\n", *returnSize);
    for(int i = 0; i < TABLE_SIZE; i++){
        printf("this is the size of floor \"%d\" : %d\n", i, (*returnColumnSizes)[i]);
    }
    int** result = convert_hash_to_2Darray(map, *returnSize, *returnColumnSizes);
    return result;
}