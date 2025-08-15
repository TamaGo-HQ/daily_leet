/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* cur = head;
    struct ListNode* past = head;
    int duplicate_val = 101;

    while(cur != NULL && cur->next != NULL){
        if(cur->val == cur->next->val){
            if(cur == head){
                duplicate_val = cur->val;
                head = head->next->next;
                cur = head;
                past = cur;
            }else{
                duplicate_val = cur->val;
                past->next = cur->next->next;
                cur = past->next;
            }
        }else if(cur->val == duplicate_val){
            if(cur == head){
                head = head->next;
                cur = head;
                past = cur;
            }else{
                past->next = cur->next;
                cur =  past->next;
            }
        }else{
            past = cur;
            cur = cur->next;
        }
    }
    if(cur!=NULL && cur->next == NULL && (cur->val == duplicate_val)){
        
        if(cur == head){
            printf("head val: %d", head->val);
            head = head->next;
        }else{
            printf("cur val: %d", cur->val);
            past->next = cur->next;
        }
    }
        return head;  
}