#ifndef TASK9_BIGINT_HPP
#define TASK9_BIGINT_HPP

#include <string>

class BigInt {
private:
    enum Comparison {
        LBIGGER,
        EQUAL,
        RBIGGER
    };

    bool m_positive;
    std::string m_number;

    static std::string add(const std::string &num1, const std::string &num2);
    static std::string subtract(const std::string &num, const std::string &minus);

    std::string karatsuba_mult(const BigInt &num) const;
    std::string fft_mult(const BigInt &num) const;

    // -1 - left bigger; 0 - equal; +1 - right bigger
    static Comparison compare(const std::string &num1, const std::string &num2);

    void operator=(int) = delete;
    void operator=(std::string) = delete;

public:
    BigInt(int num=0): m_positive(num >= 0), m_number(std::to_string(num < 0 ? -(long)num : num)) {}
    BigInt(std::string number);

    // for negative number inverse all bit and add 1
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

    explicit operator int() const;
    explicit operator std::string() const;
};


#endif //TASK9_BIGINT_HPP
