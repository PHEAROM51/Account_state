#include <iostream>

int main() {
    std::cout << "Hello, There!" << std::endl;
    std::cout << "What is your name?" << std::endl;
    std::string name;
    std::cin >> name;
    std::cout << "Nice to meet you, " << name << "!" << std::endl;
    return 0;
}