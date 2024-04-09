#ifndef LONGARITH_TEST_HPP
#define LONGARITH_TEST_HPP

#include <string>
#include "BigInt.hpp"
#include "fft.hpp"


namespace Test {
namespace detail {
    void print(const std::vector<long long> &nums, const std::string &name);
    std::string check(BigInt num1, BigInt num2, BigInt actual, char op, int test);

    void add();
    void subtract();
    void multiply();
    void division();
    void division_with_remainder();

    void binary_conversion();
    void int_conversion();
    void pow();

    void fft();

} // detail

    void start();
} // Test

#endif //LONGARITH_TEST_HPP
