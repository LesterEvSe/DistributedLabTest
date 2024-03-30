#include <iostream>
#include "maze.hpp"

int main() {
    int rows, cols;
    std::cout << "Rows and columns must be greater than 3" << std::endl;
    std::cout << "Enter rows: ";
    std::cin >> rows;

    std::cout << "Enter columns: ";
    std::cin >> cols;
    Maze maze(rows, cols);

    for (const std::vector<char> &line : maze.field()) {
        for (char ch : line)
            std::cout << ch;
        std::cout << std::endl;
    }
    return 0;
}
