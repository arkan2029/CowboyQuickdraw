#ifndef BST_HPP
#define BST_HPP

#include "node.hpp"

class BST {
    public:
        BST();
        ~BST();
        void insert(int time);
        int findMin();
    private:
        Node* root;
        void deleteTree(Node* node);
        Node* insertHelper(Node* node, int time);
        Node* findMinNode(Node* node);
};


#endif // BST_HPP