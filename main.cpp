#include <iostream>
#include <vector>
#include <fstream>

class treeNode {
public:
    int data;
    int count;
    treeNode *left, *right;
};

class tree{
public:
    treeNode *root;
    tree() : root(nullptr) {}

    void inOrder(treeNode *t){
        if (t != nullptr){
            inOrder(t->left);
            std::cout << t->data << " ";
            inOrder(t->right);
        }
    }


    treeNode *makeTreeNode(int num){
        treeNode *t = new treeNode();
        t->data = num;
        t->count = 1;
        t->left = nullptr;
        t->right = nullptr;
        return t;
    }

    void buildTree(std::vector<int>& nums, treeNode*& root) {
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            if (i == 0) {
                root = makeTreeNode(num);
            } else {
                bool searching = true;
                treeNode* t = root;
                while (searching) {
                    if (num == t->data) {
                        t->count++;
                        searching = false;
                    } else if (num < t->data) {
                        if (t->left == nullptr) {
                            t->left = makeTreeNode(num);
                            searching = false;
                        } else {
                            t = t->left;
                        }
                    } else {
                        if (t->right == nullptr) {
                            t->right = makeTreeNode(num);
                            searching = false;
                        } else {
                            t = t->right;
                        }
                    }
                }
            }
        }
    }

    treeNode *root;
};

int main() {

    tree tree{};

    std::ifstream file("numbers.txt");
    std::vector<int> nums;
    int num;
    while (file >> num){
        nums.push_back(num);
    }

    tree.buildTree(nums, tree.root);


}