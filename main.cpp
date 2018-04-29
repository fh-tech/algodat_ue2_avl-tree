#include <iostream>
#include <iomanip>
#include "Tree.h"

int main() {

    Tree<int> t{};
    t.add(10);
    t.add(11);
    t.add(9);
    t.add(8);
    t.printPreOrder();
    t.printPostOrder();
    t.printInOrder();
}

