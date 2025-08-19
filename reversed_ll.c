/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* cur_node = head;
    struct ListNode* prev_node = NULL;
    struct ListNode* next_node = NULL;
    //while cur_pointer != NULL
    //inverse the next field
    //store  @ of next node
    //change @ field to @ of previous node
    //increment
    //whencur == null
    // return address of last node as the head  

    while(cur_node != NULL){
        next_node = cur_node->next;
        cur_node->next = prev_node;
        prev_node = cur_node;
        cur_node = next_node;
    } 
    return prev_node;
}