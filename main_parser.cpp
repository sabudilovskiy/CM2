#include <iostream>
#include <string>

#include "parser.hpp"


int main() {

    std::string expression;
    std::cout << "Enter the braces expression: ";
    std::getline(std::cin, expression);
    auto parser = create_default_parser();
    bool isValid = parser.parse(expression);
    if (isValid) {
        std::cout << "The expression is valid." << std::endl;
    } else {
        std::cout << "The expression is invalid." << std::endl;
    }
    return 0;
}
