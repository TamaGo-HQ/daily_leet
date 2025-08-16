/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insert_end(struct ListNode* head, int value);
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    // philosophy is to add the numbers and create a node on the go
    struct ListNode* cur_1 = l1;
    struct ListNode* cur_2 = l2;
    struct ListNode* head = NULL;
    struct ListNode* cur = head;
    int overflow = 0;
    int addVal = 0;
    do{
        if(cur_1 != NULL && cur_2 != NULL){
            //create a new node
            //link it to the previous node
            //store the added value in it (Keep in Mind overflow)
            //new_node points to NULL
            //update overflow
            addVal = cur_1->val + cur_2->val + overflow;
            if (addVal < 10){
                head = insert_end(head, addVal);
                overflow = 0;
            }else{
                head = insert_end(head, addVal % 10);
                overflow = 1;
            }
            //update pointers
            cur_1 = cur_1->next;
            cur_2 = cur_2->next;
        }else if(cur_1 != NULL && cur_2 == NULL){
            //same but
            addVal = cur_1->val + overflow;
            if (addVal < 10){
                head = insert_end(head, addVal);
                overflow = 0;
            }else{
                head = insert_end(head, addVal % 10);
                overflow = 1;
            }
            //update only != NULL pointers
            cur_1 = cur_1->next;
        }else if(cur_1 == NULL && cur_2 !=NULL){
            addVal = cur_2->val + overflow;
            if (addVal < 10){
                head = insert_end(head, addVal);
                overflow = 0;
            }else{
                head = insert_end(head, addVal % 10);
                overflow = 1;
            }
            //update only != NULL pointers
            cur_2 = cur_2->next;
        }else if(overflow == 1){
            head = insert_end(head, 1);
            overflow = 0;
        }
    }while(cur_1 != NULL || cur_2 !=NULL); 
    //return head of new ll
    if(overflow == 1){
        head = insert_end(head, 1);
        overflow = 0;
    }    
    return head;
}

struct ListNode* insert_end(struct ListNode* head, int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = value;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // new node becomes the head
    }

    struct ListNode* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;

    return head;
}