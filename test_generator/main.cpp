//
// Created by vik on 02.05.18.
//

#include <iostream>
#include <fstream>
#include <random>

int generate_rand(int& min, int& max) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(eng);
}

int main() {
    int amount, min, max;
    std::string name;
    std::cout << "Enter amount of entries: ";
    std::cin >> amount;
    std::cout << "Enter start-range: ";
    std::cin >> min;
    std::cout << "Enter end-range: ";
    std::cin >> max;
    std::cout << "Enter filename: ";
    std::cin >> name;

    std::ofstream test_f(name);
    for(int i = 0; i < amount; i++) {
        int rand = generate_rand(min, max);
        test_f << rand << std::endl;
    }
    test_f.close();
    return 0;
}