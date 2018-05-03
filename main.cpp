#include <iostream>
#include <sstream>
#include "Tree.h"
#include "Node.h"

int main() {
    Tree<int> t{};

    std::string input;
    while(std::getline(std::cin, input)) {
        std::stringstream ss(input);
        int val;
        ss >> val;
        t.add(val);
    }
    t.printStats();
}

