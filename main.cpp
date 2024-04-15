#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

class treeNode {
public:
    int data;
    int count;
    treeNode *left, *right;

    treeNode(int num) : data(num), count(1), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    treeNode *root;
    int compareCount;

    Tree() : root(nullptr), compareCount(0) {}

    treeNode* makeTreeNode(int num) {
        return new treeNode(num);
    }

    void buildTree(const std::vector<int>& nums) {
        for (int num : nums) {
            if (!root) {
                root = makeTreeNode(num);
            } else {
                treeNode* current = root;
                while (true) {
                    compareCount++;
                    if (num == current->data) {
                        current->count++;
                        break;
                    } else if (num < current->data) {
                        if (!current->left) {
                            current->left = makeTreeNode(num);
                            break;
                        } else {
                            current = current->left;
                        }
                    } else {
                        if (!current->right) {
                            current->right = makeTreeNode(num);
                            break;
                        } else {
                            current = current->right;
                        }
                    }
                }
            }
        }
    }

    void inOrderRecursive(treeNode* node, std::ostream& os) {
        if (!node) return;
        inOrderRecursive(node->left, os);
        os << node->data << " " << node->count << std::endl;
        inOrderRecursive(node->right, os);
    }

    void inOrderIterative(std::ostream& os) {
        std::stack<treeNode*> stack;
        treeNode* current = root;
        while (!stack.empty() || current) {
            while (current) {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            os << current->data << " " << current->count << std::endl;
            current = current->right;
        }
    }

    void writeTreeToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "cant open" << std::endl;
            return;
        }
        file << "Recursive inOrder:\n";
        inOrderRecursive(root, file);

        file << "Iterative inOrder :\n";
        inOrderIterative(file);

        file << "\nComparisons: " << compareCount << std::endl;
        file.close();
    }
};

void bubbleSort(std::vector<int>& nums, int& compareCount) {
    bool swapped;
    int n = nums.size();
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            compareCount++;
            if (nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    std::ifstream file("numbers.txt");
    std::vector<int> nums;
    int num;
    while (file >> num) {
        nums.push_back(num);
    }

    Tree myTree;
    myTree.buildTree(nums);
    myTree.writeTreeToFile("sorted_tree_output.txt");

    int compareCount = 0;
    bubbleSort(nums, compareCount);
    std::ofstream sortedFile("sorted_bubble_output.txt");
    for (int number : nums) {
        sortedFile << number << std::endl;
    }
    sortedFile << "\nTotal Comparisons: " << compareCount << std::endl;

    return 0;
}
