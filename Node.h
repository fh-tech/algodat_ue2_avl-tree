//
// Created by vik on 02.05.18.
//

#ifndef UE2_AVLTREE_NODE_H
#define UE2_AVLTREE_NODE_H

template<typename T>
class Node {
public:
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    T value{};

    Node(T value) {
        this->value = value;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

#endif //UE2_AVLTREE_NODE_H
