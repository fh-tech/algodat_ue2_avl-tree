//
// Created by vik on 29.04.18.
//

#include "Tree.h"

template<typename T>
Tree<T>::Tree() {
    root = nullptr;
    size = 0;
}

template<typename T>
Tree<T>::~Tree() {
    delete root;
}

template<typename T>
void Tree<T>::add(T val) {
    root = addRecursive(root, val);
}

template<typename T>
void Tree<T>::printPreOrder() {
    size_t j = size;
    TraversePreOrder(root, [&j](Node<T> *current) mutable {
        std::cout << current->value;
        if (--j > 0) std::cout << "->";
    });
    std::cout << "\n";
}

template<typename T>
void Tree<T>::printPostOrder() {
    size_t j = size;
    TraversePostOrder(root, [&j](Node<T> *current) mutable {
        std::cout << current->value;
        if (--j > 0) std::cout << "->";
    });
    std::cout << "\n";
}

template<typename T>
void Tree<T>::printInOrder() {
    size_t j = size;
    TraverseInOrder(root, [&j](Node<T> *current) mutable {
        std::cout << current->value;
        if (--j > 0) std::cout << "->";
    });
    std::cout << "\n";
}

template<typename T>
Node<T>* Tree<T>::addRecursive(Node<T> *current, int val) {
    if (!current) {
        return new Node<T>(val);
    } else if (val > current->value) {
        current->right = addRecursive(current->right, val);
    } else if (val < current->value) {
        current->left = addRecursive(current->left, val);
    } else {
//value already exists
        return current;
    }
    size++;
    return current;
}

template<typename T>
void Tree<T>::TraversePreOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
    if (current) {
        action(current);
        TraversePreOrder(current->left, action);
        TraversePreOrder(current->right, action);
    }
}

template<typename T>
void Tree<T>::TraversePostOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
    if (current) {
        TraversePostOrder(current->left, action);
        TraversePostOrder(current->right, action);
        action(current);
    }
}

template<typename T>
void Tree<T>::TraverseInOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
    if (current) {
        TraverseInOrder(current->left, action);
        action(current);
        TraverseInOrder(current->right, action);
    }
}









