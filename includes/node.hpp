#ifndef NODE_HPP
#define NODE_HPP

struct Node {
    int time;
    Node* left;
    Node* right;
    Node(int t) : time(t), left(nullptr), right(nullptr) {}
};

#endif // NODE_HPP