struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

// O(n), O(1)
class Solution {
public:
   void connect(TreeLinkNode *root) {
       if(!root) return;
       if(root->left) {
           root->left->next = root->right;
           if(root->next) {
               root->right->next = root->next->left;
           }
       }
       connect(root->left);
       connect(root->right);
       return;
   }
};

// O(n), O(1)
// BFS
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode* start = root;
        while(start) {
            TreeLinkNode* cur = start;
            while(cur) {
                if(cur->left) {
                    cur->left->next = cur->right;
                }
                if(cur->right && cur->next) {
                    cur->right->next = cur->next->left;
                }
                cur = cur->next;
            }
            start = start->left;
        }
    }
};
