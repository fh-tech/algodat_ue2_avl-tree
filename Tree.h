//
// Created by viktor on 29.04.18.
//

#ifndef UE2_AVLTREE_TREE_H
#define UE2_AVLTREE_TREE_H

#include <functional>
#include <iostream>

//TODO: how to use this lambda in all print functions? can not caputre non-variable SIZE
//template<std::size_t SIZE>
//auto printTree = [&SIZE](Node* current) -> void mutable {
//    std::cout << current->value;
//    if (--SIZE > 0) std::cout << "->";
//};

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

template<typename T>
class Tree {
public:
    Tree();
    // if i delete the tree all Nodes go out of scope and call their destructor!
    ~Tree();
    void add(T val);
    void printPreOrder();
    void printPostOrder();
    void printInOrder();


private:
    Node<T> *root = nullptr;
    size_t size{};

    Node<T> *addRecursive(Node<T> *current, int val);
    void TraversePreOrder(Node<T> *current, std::function<void(Node<T> *)> action);
    void TraversePostOrder(Node<T> *current, std::function<void(Node<T> *)> action);
    void TraverseInOrder(Node<T> *current, std::function<void(Node<T> *)> action);
};


#endif //UE2_AVLTREE_TREE_H
