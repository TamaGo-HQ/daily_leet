/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* detectCycle(struct ListNode* head) {
    struct ListNode* hare = head;
    struct ListNode* turt = head;
    bool same_node_alert = false;

    while ((hare != NULL) && (hare->next != NULL) && (same_node_alert == false)) {
        // advance 1 step turt and 2 step hare
        hare = hare->next->next;
        turt = turt->next;

        // check if they're at the same node
        if (hare == turt) {
            same_node_alert = true;
        }
    }
    
    //respawn turt to start and leave hare as it is
    turt = head;

    //move them at the same speed and report where they first meet
    while(same_node_alert == true){
        if(turt == hare){
            return hare;
        }
        turt = turt->next;
        hare = hare->next;
    }

    //execution only gets here if there is no
    return NULL;
}