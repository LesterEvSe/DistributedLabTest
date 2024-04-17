#include <iostream>
#include "CSVHandler.hpp"

int main() {
    std::cout << "Enter the full or relative path of the file.\n";
    std::cout << "For example '/home/user1/code/data.csv' or code/data.csv\n" << std::endl;
    std::string data1, data2;

    std::cout << "Enter the first file path: ";
    std::getline(std::cin, data1);
    std::cout << "Enter the second file path: ";
    std::getline(std::cin, data2);

    CSVHandler(data1, data2).print_answer();
    return 0;
}
