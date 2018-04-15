//
// Created by daniel on 15.04.18.
//

#ifndef UE2_AVLTREE_TREE_H
#define UE2_AVLTREE_TREE_H

#include <memory>
#include <functional>
#include <cassert>

struct node_visiter;

struct node {
    std::unique_ptr<node> left{};
    std::unique_ptr<node> right{};
    std::unique_ptr<int>  val{};

    node() = default;

    int height(){
        if(!left && !right){
            return val? 1 : 0;
        }else{
            return 1 + std::max( left  ? left ->height(): 0
                           , right ? right->height(): 0);
        }
    }

    void add(int newval){
        std::unique_ptr<node>* direction = nullptr;

        if(!val) this->val = std::make_unique<int>(newval);

        else {
            if(newval == *val) return;

            if(newval < *val) direction = &left;
            if(newval > *val) direction = &right;
            if(!(*direction)){
                (*direction) = std::make_unique<node>();
            }
            (*direction)->add(newval);
        }
    }

    int balance() {
        return   (left  ? left ->height() : 0)
               - (right ? right->height() : 0);
    }
};

class Tree {
private:
    std::unique_ptr<node> root = std::make_unique<node>();
public:

    Tree()= default;

    void add(int i){
        root->add(i);
    }

    int get_height(){
        return root->height();
    }

    int get_balance(){
        return root->balance();
    }

    template <typename T>
    T acc(std::function<T (node*)> fn) {
        assert(this->root);
        return rec_fold(fn, this->root.get());
    }

private:
    template <typename T>
    T rec_fold(const std::function<T (node*)> &fn, node* tree){
        auto t = T{};
        if(tree) {
            if (tree->left) {
                t = t + rec_fold(fn, tree->left.get());
            }
            if (tree->val) {
                t = t + fn(tree);
            }
            if (tree->right) {
                t = t + rec_fold(fn, tree->right.get());
            }
        }
        return t;
    }
};

struct node_visiter{

    node_visiter() = default;

    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();

    double avg = 0;
    int i = 0;

    bool avl = true;


//fucking monoids, they are everywhere
    node_visiter operator+(const node_visiter &other) {
        auto navg = 0.0;
        if(this->i != 0 || other.i != 0){
            navg = ((this->avg * this->i) + (other.avg * other.i)) / (this->i + other.i);
        }

        auto ret = (node_visiter) {
            .min = std::min(this->min, other.min),
            .max = std::max(this->max, other.max),
            .avg = navg,
            .i = this->i + other.i,
            .avl = this->avl && other.avl
        };
        return ret;
    }
};

#endif //UE2_AVLTREE_TREE_H
