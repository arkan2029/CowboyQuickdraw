#include "../includes/bst.hpp"
#include <stdexcept>

//constructor
BST::BST() : root(nullptr) {}

//destructor
BST::~BST() {
    deleteTree(root);
}

//recursive destructor helper
void BST::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

//insert node
void BST::insert(int time) {
    root = insertHelper(root, time);
}

//recursive insertion helper
Node* BST::insertHelper(Node* node, int time) {
    if (node == nullptr) {
        return new Node(time);
    }

    if (time < node->time) {
        node->left = insertHelper(node->left, time);
    } else {
        node->right = insertHelper(node->right, time);
    }

    return node;
}

//public getter to receive best time
int BST::findMin() {
    if (root == nullptr) {
        throw std::runtime_error("BST is empty");
    }
    Node* minNode = findMinNode(root);
    return minNode->time;
}

//recursive getter helper
Node* BST::findMinNode(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
