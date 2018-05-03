//
// Created by viktor on 29.04.18.
//

#ifndef UE2_AVLTREE_TREE_H
#define UE2_AVLTREE_TREE_H

#include <functional>
#include <iostream>
#include "Node.h"
#include <limits>
#include <iomanip>

struct recursion_state {
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    long long sum = 0;
    int count = 0;
    bool avl = true;
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
//    void printPreOrder() {
//        TraversePreOrder(root, print<T>);
//    }
//    void printPostOrder() {
//        TraversePostOrder(root, print<T>);
//    }
//    void printInOrder() {
//        TraverseInOrder(root, print<T>);
//    }
    void printStats() {
        recursion_state stat_res = TraverseSpecial<recursion_state>(root, recursion_state{}, [](recursion_state rec_state, Node<T>* current) {
            int height_left = get_height(current->left);
            int height_right = get_height(current->right);
            int balance = height_left - height_right;
            std::cout << "bal(" << current->value << ") = " << balance;
            if(balance*balance >= 4) {
                std::cout << " (AVL violation!)" << std::endl;
                rec_state.avl = false;
            } else {
                std::cout << "\n";
            }
            if(current->value > rec_state.max) rec_state.max = current->value;
            if(current->value < rec_state.min) rec_state.min = current->value;
            rec_state.sum += current->value;
            rec_state.count += 1;
            return rec_state;
        });
            double avg = stat_res.count > 0 ? (double)stat_res.sum / stat_res.count : 0;
            stat_res.avl ? std::cout << "AVL: yes" << std::endl : std::cout << "AVL: no" << std::endl;
            std::cout << "min: " << (stat_res.count > 0 ? stat_res.min : 0) << ", max: " << (stat_res.count > 0 ? stat_res.max : 0) << ", avg: " << std::fixed << std::setprecision(2) << avg << std::endl;


        }


private:
    Node<T> *root = nullptr;

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
        return current;
    }

    // traverses like in pdf - reversed post order?
    template<typename J>
    J TraverseSpecial(Node<T> *current, J rec_state, std::function<J(J, Node<T> *)> action) {
        if(current) {
            rec_state = TraverseSpecial(current->right, rec_state, action);
            rec_state = TraverseSpecial(current->left, rec_state, action);
            rec_state =  action(rec_state, current);
        }
        return rec_state;
    }

//    void TraversePreOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
//        if (current) {
//            action(current);
//            TraversePreOrder(current->left, action);
//            TraversePreOrder(current->right, action);
//        }
//    }
//
//    void TraversePostOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
//        if (current) {
//            TraversePostOrder(current->left, action);
//            TraversePostOrder(current->right, action);
//            action(current);
//        }
//    }
//
//    void TraverseInOrder(Node<T> *current, std::function<void(Node<T> *)> action) {
//        if (current) {
//            TraverseInOrder(current->left, action);
//            action(current);
//            TraverseInOrder(current->right, action);
//        }
//    }

    // static so i can call it in lambda
    static int get_height(Node<T>* node){
        if(!node) return 0;
        else{
            return 1 + std::max(
                    get_height(node->left),
                    get_height(node->right)
            );
        }
    }
};


#endif //UE2_AVLTREE_TREE_H
