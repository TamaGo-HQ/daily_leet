/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* cur = head;
    while(cur != NULL && cur->next != NULL){
        //compare with next
        if(cur-> val == cur->next->val){
            cur->next = cur->next->next;
        }else {
            //only advance when the next node is not a duplicate 
            if(cur != NULL)
            cur = cur->next;
        }
    }
    return head;
}