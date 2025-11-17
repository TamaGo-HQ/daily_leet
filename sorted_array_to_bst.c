/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* add_node_balanced(int* array, int low, int high){
    if(low > high){
        return NULL;
    }

    int middle = (low + high) / 2;

    struct TreeNode* root = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    root->val = array[middle];
    root->left = add_node_balanced(array, low, middle - 1);
    root->right = add_node_balanced(array, middle + 1, high);
    return root;
}


struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    return add_node_balanced(nums, 0, numsSize - 1);
}