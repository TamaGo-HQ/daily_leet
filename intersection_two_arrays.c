/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 #define TABLE_SIZE 500

 typedef struct element_t{
    int key;
    bool is_intersection;
    struct element_t* next;
 }element_t;

 typedef struct hashmap{
    element_t* table[TABLE_SIZE];
}hashmap_t;


hashmap_t* create_hashmap() {
    hashmap_t* map = malloc(sizeof(hashmap_t));
    for (int i = 0; i < TABLE_SIZE; i++)
        map->table[i] = NULL;
    return map;
}

unsigned int hash(int key){
    return key % TABLE_SIZE;
}

void hashmap_put(hashmap_t* map, int key) {
    unsigned int idx = hash(key);
    element_t* cur = map->table[idx];

    // Look for existing key
    while (cur != NULL) {
        if (cur->key == key) {
            return; // Key already exists, do nothing
        }
        cur = cur->next;
    }

    // Create new element and insert at head of list
    element_t* new_elem = malloc(sizeof(element_t));
    new_elem->key = key;
    new_elem->is_intersection = false;
    new_elem->next = map->table[idx];
    map->table[idx] = new_elem;
}

void hashmap_print(hashmap_t* map) {
    if (map == NULL) {
        printf("Hashmap is NULL\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        element_t* cur = map->table[i];
        if (cur != NULL) {
            printf("Bucket[%d]: ", i);
            while (cur != NULL) {
                printf("{key: %d, is_intersection: %s} -> ",
                       cur->key,
                       cur->is_intersection ? "true" : "false");
                cur = cur->next;
            }
            printf("NULL\n");
        }
    }
}

element_t* is_in_hashmap(hashmap_t* map, int key){
    unsigned int idx = hash(key);
    element_t* cur = map->table[idx];

    while(cur != NULL){
        if(cur->key == key){
            if(cur->is_intersection == false){
                cur->is_intersection = true;
                return cur;
            }else{
                return NULL;
            }
        }
        cur = cur->next;
    }

    return NULL;
}

void hashmap_free(hashmap_t* map) {
    if (map == NULL) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        element_t* cur = map->table[i];
        while (cur != NULL) {
            element_t* tmp = cur;
            cur = cur->next;
            free(tmp);   // free each element
        }
        map->table[i] = NULL;
    }
    free(map); // finally free the hashmap struct itself
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    //create the empty map
    hashmap_t* map = create_hashmap();
    //know which is the smallest array for less memory allocation
    int  smallSize = (nums1Size < nums2Size) ? nums1Size : nums2Size;
    int* numsSmall = (nums1Size < nums2Size) ? nums1 : nums2;
    int  bigSize = (nums1Size < nums2Size) ? nums2Size : nums1Size;
    int* numsBig = (nums1Size < nums2Size) ? nums2 : nums1;

    //take smallest array and put its unique values in hash
    for(int i = 0; i < smallSize; i++){
        //this put function will intially intiate the is_intersection as false
        //will only create new element a value once, so there is no redundant values
        hashmap_put(map, numsSmall[i]);
    }

    element_t* cur = NULL;
    *returnSize = 0;
    int* result = malloc(smallSize * sizeof(int));

    for(int i = 0; i < bigSize; i++){
        //if the value exists in hashmap, check if is_intersection is already true
        //if false, turn it true and put the value in the return array
        //else, don't do anything
        cur = is_in_hashmap(map, numsBig[i]);
        if (cur != NULL){
            result[*returnSize] = cur->key;
            (*returnSize)++;
        }
    }

    hashmap_free(map);
    return result;
}