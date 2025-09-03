/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct{
    int sum;
    int i,j; //indices in nums1 and nums2
} pair_info;

typedef struct{
    pair_info* data;
    int size;
    int capacity;
} min_heap;

min_heap* create_min_heap(int capacity){
    min_heap* h = malloc(sizeof(min_heap));
    h->data = malloc(capacity * sizeof(pair_info));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heapify_up_min(min_heap* h, int idx){
    while(idx > 0){
        int parent = (idx - 1) / 2;
        //if child is smaller than parent -> swap
        if(h->data[idx].sum > h->data[parent].sum)
            break;
        pair_info temp = h->data[idx];
        h->data[idx] = h->data[parent];
        h->data[parent] = temp;
        idx = parent;
    }
}

void heapify_down_min(min_heap* h, int idx){
    while(1){
        int left = 2*idx + 1;
        int right = 2*idx + 2;
        int smallest = idx;

        if(left < h->size && h->data[left].sum < h->data[smallest].sum)
            smallest = left;
        if(right < h->size && h->data[right].sum < h->data[smallest].sum)
            smallest = right;
        if(smallest == idx)
            break;
        //swap current node with smallest chile
        pair_info temp = h->data[idx];
        h->data[idx] = h->data[smallest];
        h->data[smallest] = temp;
        idx = smallest;
        
    }
}

void heap_push_min(min_heap* h, pair_info node){
    if(h->size < h->capacity){
        h->data[h->size] = node;
        heapify_up_min(h, h->size);
        h->size++;
    }
}

pair_info heap_pop_min(min_heap* h){
    //what if it is empty
    pair_info root = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    if(h->size >0){
        heapify_down_min(h, 0);
    }
    return root;
}

void free_min_heap(min_heap* h){
    free(h->data);
    free(h);
}

int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSizes) {
    *returnSize = k;
    *returnColumnSizes = malloc (k * sizeof(int));
    int** result = malloc(k * sizeof(int*));

    min_heap* heap = create_min_heap(k);

    //create initial heap with nums1[0]
    for (int j = 0; j < nums2Size; j++){
        pair_info p;
        p.sum = nums1[0] + nums2[j];
        p.i = 0;
        p.j = j;
        heap_push_min(heap, p);
    }

    for(int count = 0; count < k && heap->size >0; count++){

        //extract the heap's root
        pair_info current = heap_pop_min(heap);
        result[count] = malloc(2 * sizeof(int));
        result[count][0] = nums1[current.i];
        result[count][1] = nums2[current.j];
        (*returnColumnSizes)[count] = 2;


        if(current.i + 1 < nums1Size){
            pair_info next;
            next.sum = nums1[current.i + 1] + nums2[current.j];
            next.i = current.i + 1;
            next.j = current.j;
            heap_push_min(heap, next);
        }
    }

    free_min_heap(heap);

    return result;
}