#include <iostream>
#include <iomanip>
#include "Tree.h"

node_visiter visit_node(node* n){
    node_visiter vist{};
    if(n->val){
        vist.max = *n->val;
        vist.min = *n->val;
        vist.i = 1;
        vist.avg = *n->val;
    }
    auto bal = n->balance();
    if(bal*bal >= 4){
        vist.avl = false;
        std::cout << "bal("<< *n->val <<") = "<< bal <<" (AVL violation!)" << std::endl;
    }else{
        std::cout << "bal("<< *n->val <<") = "<< bal << std::endl;
    }
    return vist;
}

int main() {
    Tree t{};

    t.add(10);

    t.add(12);

    t.add(8);

    t.add(11);

    t.add(9);

    t.add(13);

    auto nv = t.acc<node_visiter>(visit_node);
    if(nv.avl){
        std::cout << "AVL: yes\n";
    }else{
        std::cout << "AVL: no\n";
    }
    std::cout << "min: " << nv.min << ", max: " << nv.max << ", avg:" << std::fixed << std::showpoint << std::setprecision(1) << nv.avg << std::endl;
}

