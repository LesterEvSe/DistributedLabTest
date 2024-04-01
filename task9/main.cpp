#include <iostream>
#include "BigInt.hpp"

// Using test from https://raw.githubusercontent.com/microsoft/rego-cpp/main/tests/bigint.yaml
std::string check(BigInt actual, BigInt expected) {
    return std::string(actual == expected ? "true" : "false") + "\n";
}

void plus_and_minus_tests() {
    BigInt num1, num2;
    num1 = -2;
    num2 = -15;
    std::cout << check(num1 + num2, BigInt(-17));

    num1 = BigInt(-3796);
    num2 = BigInt(4047);
    std::cout << check(num1 + num2, BigInt(251));

    num1 = BigInt(-253534);
    num2 = BigInt(-214311);
    std::cout << check(num1 + num2, BigInt(-467845));

    num1 = BigInt("187224985");
    num2 = BigInt("235111630");
    std::cout << check(num1 + num2, BigInt("422336615"));

    num1 = BigInt();
    num2 = BigInt(12124);
    std::cout << check(num1 + num2, num2);

    num1 = BigInt("6466055601279126416241593829827225642974873054416615134420424370024610277048");
    num2 = BigInt("812377893613439962506223192889271172721150454313527119829598533028254192660");
    std::cout << check(num1 + num2, BigInt("7278433494892566378747817022716496815696023508730142254250022903052864469708"));
}

int main() {
    // std::cout << std::string(BigInt("-22222222222222222")) << std::endl;
    plus_and_minus_tests();
    return 0;
}
