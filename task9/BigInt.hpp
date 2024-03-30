#ifndef TASK9_BIGINT_HPP
#define TASK9_BIGINT_HPP

#include <string>

class BigInt {
private:
    std::string m_number;

public:
    BigInt(int num): m_number(std::to_string(num)) {}
    BigInt(const std::string &number);

    std::string binary() const;
    BigInt pow(const BigInt &step) const;

    BigInt operator+(const BigInt &num) const;
    BigInt operator-(const BigInt &num) const;
    BigInt operator*(const BigInt &num) const;
    BigInt operator/(const BigInt &num) const;
    BigInt operator%(const BigInt &num) const;

    bool operator<(const BigInt &num) const;
    bool operator>(const BigInt &num) const;
    bool operator<=(const BigInt &num) const;
    bool operator>=(const BigInt &num) const;
    bool operator==(const BigInt &num) const;

    operator int() const;
    operator std::string() const;
};


#endif //TASK9_BIGINT_HPP
