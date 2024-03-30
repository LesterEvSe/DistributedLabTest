#include "BigInt.hpp"
#include <stdexcept>


BigInt::BigInt(const std::string &number) {
    if (number.empty()) {
        m_number = "0";
        return;
    }

    int i = 0;
    if (number[i] == '-') {
        m_number += '-';
        ++i;
    } else if (number[i] == '+')
        ++i;

    while (i < number.size()) {
        if (!isdigit(number[i]))
            throw std::runtime_error("Incorrect number");
        m_number += number[i++];
    }
}



BigInt::operator int() const {
    return std::stoi(m_number);
}
BigInt::operator std::string() const {
    return m_number;
}