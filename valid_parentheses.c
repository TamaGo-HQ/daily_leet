// typedef struct ListNode {
//     int val;
//     struct ListNode* next;
// } ListNode;

int getCode(char c) {
    switch(c) {
        case '(': return 1;
        case ')': return -1;
        case '[': return 2;
        case ']': return -2;
        case '{': return 3;
        case '}': return -3;
    }
    return 0; // invalid char
}

int push(struct ListNode** head, int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if(!newNode) return 0;
    newNode->val = value;
    newNode->next = *head;
    *head = newNode;
    return 1;
}


bool isValid(char* s) {
    struct ListNode* code_stack = NULL;
    char* cur_c = s;
    int cur_code =0;
    struct ListNode* temp = NULL;

    while(*cur_c !='\0'){
        cur_code = getCode(*cur_c);
        if(cur_code > 0){
            push(&code_stack, cur_code);
        }else{
            if(code_stack == NULL || (code_stack->val + cur_code) != 0){
                return false;
            }else{

                temp = code_stack;
                code_stack = code_stack->next;
                free(temp);
            }
        }
        cur_c++;
    }
    
    if(code_stack != NULL){
        return false;
    }
    return true;
}

