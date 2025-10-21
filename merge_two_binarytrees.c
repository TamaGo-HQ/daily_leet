/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2) {

    if(root1 == NULL && root2 == NULL){
        return NULL;
    }

    struct TreeNode* root_new = malloc(sizeof(struct TreeNode));

    if(root1 == NULL){
        root_new->val = root2->val;
        root_new->right = mergeTrees(NULL, root2->right);
        root_new->left  = mergeTrees(NULL, root2->left);
        return root_new;
    }

    if(root2 == NULL){
        root_new->val = root1->val;
        root_new->right = mergeTrees(root1->right, NULL);
        root_new->left  = mergeTrees(root1->left, NULL);
        return root_new;
    }    

    root_new->val = root1->val + root2->val;
    root_new->right = mergeTrees(root1->right, root2->right);
    root_new->left  = mergeTrees(root1->left, root2->left);
    return root_new;    
}