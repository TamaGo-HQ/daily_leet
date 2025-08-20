



// ---- Problem struct ----
typedef struct {
    int k;        // size limit
    int *arr;     // sorted ascending, holds up to k largest values
    int size;     // current number of elements in arr (<= k)
} KthLargest;

// Forward decl
static void insert_sorted_bounded(int *arr, int *size, int cap, int val);

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* obj = (KthLargest*) malloc(sizeof(KthLargest));
    if (obj == NULL) return NULL;

    obj->k = k;
    obj->arr = (int*) malloc(k * sizeof(int));
    if (!obj->arr) { free(obj); return NULL; }
    
    obj->size = 0;
    // Insert initial stream values, keeping only the k largest
    for (int i = 0; i < numsSize; ++i) {
        insert_sorted_bounded(obj->arr, &obj->size, obj->k, nums[i]);
    }
    return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
    //search where3 to add it in the already sorted list to keep it sorted
    insert_sorted_bounded(obj->arr, &obj->size, obj->k, val);
    //return element of kth indice+1
    return obj->arr[0];
}

void kthLargestFree(KthLargest* obj) {
    if (!obj) return;
    free(obj->arr);
    free(obj);
}

static void insert_sorted_bounded(int *arr, int *size, int cap, int val){
    //buffer not full
    if(*size < cap){ 
        //normal sorted insert
        int i = *size - 1;
        while (i >= 0 && arr[i] > val) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = val;
        (*size)++;
        return;
    }

    //buffer full
    if (val <= arr[0]) {
        return; // too small to affect k-th largest
    }

    // Replace smallest and bubble it right until order restored
    arr[0] = val;
    int i = 0;
    while (i + 1 < cap && arr[i] > arr[i + 1]) {
        int tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
        i++;
    }
}

/**
 * Your KthLargest struct will be instantiated and called as such:
 * KthLargest* obj = kthLargestCreate(k, nums, numsSize);
 * int param_1 = kthLargestAdd(obj, val);
 
 * kthLargestFree(obj);
*/