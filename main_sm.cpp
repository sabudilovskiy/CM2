#include <iostream>
#include <string>

#include "state_machine.hpp"


int main() {

    std::string expression;
    std::cout << "Enter the braces expression: ";
    std::getline(std::cin, expression);
    auto sm = create_default();
    bool isValid = sm.parse(expression);
    if (isValid) {
        std::cout << "The expression is valid." << std::endl;
    } else {
        std::cout << "The expression is invalid." << std::endl;
    }
    return 0;
}
