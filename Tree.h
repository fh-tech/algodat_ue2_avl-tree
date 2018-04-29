//
// Created by viktor on 29.04.18.
//

#ifndef UE2_AVLTREE_TREE_H
#define UE2_AVLTREE_TREE_H

#include <memory>
#include <functional>

template<typename T>
class Node {
public:
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
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
    Node<T>* root = nullptr;
    size_t size{};

    void add(T val) {
        root = addRecursive(root, val);
    }

    void printPreOrder() {
        size_t j = size;
        TraversePreOrder(root, [&j](Node<T>* current) mutable{
            std::cout << current->value;
            if(--j > 0) std::cout << "->";
        });
        std::cout << "\n";
    }

    void printPostOrder() {
        size_t j = size;
        TraversePostOrder(root, [&j](Node<T>* current) mutable{
            std::cout << current->value;
            if(--j > 0) std::cout << "->";
        });
        std::cout << "\n";
    }

    // closure with size of tree
    void printInOrder() {
        size_t j = size;
        TraverseInOrder(root, [&j](Node<T>* current) mutable{
            std::cout << current->value;
            if(--j > 0) std::cout << "->";
        });
        std::cout << "\n";
    }



    Tree() {
        root = nullptr;
        size = 0;
    }
//    ~Tree() {
//        TraverseInOrder(root, [](Node<T>* current) -> void {delete current;});
//    }

private:
    Node<T>* addRecursive(Node<T>* current, int val) {
        if(!current) {
            return new Node(val);
        } else if(val > current->value) {
            current->right = addRecursive(current->right, val);
        } else if(val < current->value) {
            current->left = addRecursive(current->left, val);
        } else {
            //value already exists
            return current;
        }
        size++;
        return current;
    }

    void TraversePreOrder(Node<T>* current, std::function<void(Node<T>*)> action) {
        if(!current) {
            return;
        } else {
            action(current);
            TraversePreOrder(current->left, action);
            TraversePreOrder(current->right, action);
        }
    }

    void TraversePostOrder(Node<T>* current, std::function<void(Node<T>*)> action) {
        if(!current) {
            return;
        } else {
            TraversePostOrder(current->left, action);
            TraversePostOrder(current->right, action);
            action(current);
        }
    }

    void TraverseInOrder(Node<T>* current, std::function<void(Node<T>*)> action) {
        if(!current) {
            return;
        } else {
            TraverseInOrder(current->left, action);
            action(current);
            TraverseInOrder(current->right, action);
        }
    }
};



#endif //UE2_AVLTREE_TREE_H
