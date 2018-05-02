//
// Created by viktor on 29.04.18.
//

#ifndef UE2_AVLTREE_TREE_H
#define UE2_AVLTREE_TREE_H

#include <functional>
#include <iostream>
#include "Node.h"

//lambda for printing
template<typename T>
auto print = [](Node<T>* current) {
    std::cout << current->value << std::endl;
};

struct recursion_state {
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    int sum = 0;
    int count = 0;
};

template<typename T>
class Tree {
public:
    Tree() = default;
    // if i delete the tree all Nodes go out of scope and call their destructor!
    ~Tree() {
        delete root;
    }
    void add(T val) {
        root = addRecursive(root, val);
    }
    void printPreOrder() {
        TraversePreOrder(root, print<T>);
    }
    void printPostOrder() {
        TraversePostOrder(root, print<T>);
    }
    void printInOrder() {
        TraverseInOrder(root, print<T>);
    }
    void printStats() {
        recursion_state rec_stat = TraverseSpecial<recursion_state>(root, recursion_state{}, [](recursion_state rec_state, Node<T>* current) {
            if(current->value > rec_state.max) rec_state.max = current->value;
            if(current->value < rec_state.min) rec_state.min = current->value;
            rec_state.sum += current->value;
            rec_state.count += 1;
        });
        double avg = rec_stat.sum / rec_stat.count;
        std::cout << "min: " << rec_stat.min << ", max: " << rec_stat.max << ", avg: " << avg << std::endl;
    }


private:
    Node<T> *root = nullptr;
    size_t size{};

    Node<T> *addRecursive(Node<T> *current, int val) {
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
    void TraversePreOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
        if (current) {
            action(current);
            TraversePreOrder(current->left, action);
            TraversePreOrder(current->right, action);
        }
    }
    void TraversePostOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
        if (current) {
            TraversePostOrder(current->left, action);
            TraversePostOrder(current->right, action);
            action(current);
        }
    }
    template<typename J>
    J TraverseSpecial(Node<T> *current, J rec_state, std::function<J(J, Node<T> *)> action) {
        if(current) {
            rec_state = TraverseSpecial(current->right, rec_state, action);
            rec_state = TraverseSpecial(current->left, rec_state, action);
            rec_state =  action(rec_state, current);
        }
        return rec_state;
    }

    void TraverseInOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
        if (current) {
            TraverseInOrder(current->left, action);
            action(current);
            TraverseInOrder(current->right, action);
        }
    }

    T getMin(Node<T>* current) {
        if(current->left) {
            getMin(current->left);
        }
        return current;
    }

    T getMax(Node<T>* current) {
        if(current->right) {
            getMax(current->right);
        }
        return current;
    }

};


#endif //UE2_AVLTREE_TREE_H
