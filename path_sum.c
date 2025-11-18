/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode* root, int targetSum) {

    //empty node
    if(root == NULL) return false;

    //leaf node
    if (root->left == NULL && root->right == NULL){
        if(root->val == targetSum){
            return true;
        }else return false;
    }

    //trunk node
    targetSum = targetSum - root->val;
    if (hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum))
        return true;
    
    return false;
}