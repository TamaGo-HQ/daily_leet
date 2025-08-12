/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode* head) {

    struct ListNode* hare = head;
    struct ListNode* turt = head;

    while ((hare != NULL) && (hare->next != NULL)) {

        hare = hare->next->next;
        turt = turt->next;

        if (hare == turt) {
            return true;
        }
    }

    return false;
}