/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define TABLE_SIZE 1000

typedef struct Element_t{
    int key;     // the number itself (nums[i])
    int index;   // the position in nums
    struct Element_t* next;
} Element_t;

 typedef struct{
    Element_t * table[TABLE_SIZE];
 }HashMap_t;

 unsigned int hash(int key){
    return abs(key) % TABLE_SIZE;
 }

 HashMap_t* create_hashmap(){
    HashMap_t* result = (HashMap_t*) malloc(sizeof(HashMap_t));
    for(int i = 0; i < TABLE_SIZE; i++){
        result->table[i] = NULL;
    }
    return result;
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

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    //create hashmap containing all elements & their indices
    HashMap_t* map = create_hashmap();
    *returnSize = 2;
    int* result = malloc (2*sizeof(int));
    for(int i = 0; i < numsSize; i++){
        //create the element
        Element_t* element = malloc(sizeof(Element_t));
        element->key = nums[i];
        element->index = i;
        element->next = NULL;
        //push it to the map
        put_hashmap(map, element);
    }

    for(int i = 0; i < numsSize; i++){
        //calculate complement
        //in this problem we know for sure that the complement exists
        int cmp_key = target - nums[i];
        unsigned int cmp_idx = hash(cmp_key);
        Element_t* cmp_el = map->table[cmp_idx];
        while(cmp_el != NULL){
            if ((cmp_el->key == cmp_key) && (cmp_el->index != i)){
                result[0] = i;
                result[1] = cmp_el->index;
                break;
            }
            cmp_el = cmp_el->next;
        }
    }
    return result;
}