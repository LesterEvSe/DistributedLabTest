#include "BigInt.hpp"
#include "fft.hpp"

#include <stdexcept>
#include <iostream> // for testing


// helper methods
std::string BigInt::add(const std::string &num1, const std::string &num2) {
    std::string answer;
    int sum = 0, i = num1.size()-1, j = num2.size()-1;

    while (i >= 0 || j >= 0 || sum) {
        if (i >= 0) sum += num1[i--] - '0';
        if (j >= 0) sum += num2[j--] - '0';

        answer += (sum % 10) + '0';
        sum /= 10;
    }

    swap_str(answer);
    return answer;
}

// Assume that num will always be less than minus
std::string BigInt::subtract(const std::string &num, const std::string &minus) {
    std::string answer;
    int curr = 0, i = num.size()-1, j = minus.size()-1;

    while (i >= 0 || j >= 0 || curr) {
        int sum = num[i--] - '0' + curr;
        if (j >= 0) sum -= minus[j--] - '0';

        if (sum < 0) {
            curr = -1;
            sum += 10;
        } else
            curr = 0;

        answer += sum + '0';
    }

    // Get rid of leading zeros
    while (answer.back() == '0')
        answer.pop_back();

    swap_str(answer);
    return answer;
}

// Long Division algorithm. Standard algorithm from elementary school
/*
  When dividing, we get the result and the remainder,
  so depending on the Boolean variable we return the desired value
 */
std::string BigInt::divide(const std::string &num, const std::string &den, bool _remainder) {
    if (den == "0")
        throw std::runtime_error("Zero Division Error");

    std::string res;
    std::string remainder = num.substr(0, den.size()-1);

    for (int i = remainder.size(); i < num.size(); ++i) {
        remainder += num[i];
        char digit = '0';

        while (compare(remainder, den) != RBIGGER) {
            remainder = subtract(remainder, den);
            ++digit;
        }
        if (!res.empty() || digit != '0')
            res += digit;
    }

    if (_remainder) return remainder;
    return res;
}

std::string BigInt::divide_by_two(const std::string &num) {
    std::string res;
    const short divisor = 2;
    short remainder = 0;

    for (int i = 0; i < num.size(); ++i) {
        remainder = remainder*10 + num[i]-'0';
        if (remainder < divisor && res.empty()) continue;
        res += remainder/2 + '0';
        remainder %= 2;
    }
    return res;
}

void BigInt::swap_str(std::string &number) {
    for (int i = 0, j = number.size()-1; i < j; ++i, --j)
        std::swap(number[i], number[j]);
}

std::string BigInt::bin(std::string num) {
    std::string bin;
    while (!num.empty()) {
        bool last_bit = (num.back()-'0')%2;
        bin += last_bit ? '1' : '0';
        num = divide_by_two(num);
    }
    return bin;
}


BigInt::Comparison BigInt::compare(const std::string &num1, const std::string &num2) {
    if (num1.size() != num2.size()) return num1.size() > num2.size() ? LBIGGER : RBIGGER;
    for (int i = 0; i < num1.size(); ++i) {
        if (num1[i] > num2[i]) return LBIGGER;
        else if (num1[i] < num2[i]) return RBIGGER;
    }
    return EQUAL;
}

std::string BigInt::karatsuba_mult(std::string num, std::string mul)
{
    if (num.size() == mul.size() && num.size() == 1)
        return std::to_string((num[0] - '0') * (mul[0] - '0'));
    if (num == "0" || mul == "0")
        return "0";

    // Work Good
    size_t n = std::max(num.size(), mul.size());
    n += n & 1;
    const size_t half = n >> 1;

    num = std::string(n - num.size(), '0') + num;
    mul = std::string(n - mul.size(), '0') + mul;

    std::string Al, Ar, Bl, Br;
    for (int i = 0; i < half; ++i) {
        Al += num[i];
        Bl += mul[i];
        Ar += num[half + i];
        Br += mul[half + i];
    }

    std::string p = karatsuba_mult(Al, Bl);
    std::string q = karatsuba_mult(Ar, Br);
    std::string res = subtract(karatsuba_mult(add(Al, Ar), add(Bl, Br)), add(p, q));

    // Multiply p and res by 10^n and 10^(n/2) respectively
    for (int i = 0; i < n; ++i) p += '0';
    for (int i = 0; i < half; ++i) res += '0';
    std::string ans = add(p, add(q, res));

    // remove leading zeros
    int i = 0;
    while (i < ans.size() && ans[i] == '0') ++i;

    if (i == ans.size()) return "0";
    return ans.substr(i);
}


std::string BigInt::fft_mult(const std::string &num, const std::string &mul) {
    std::vector<long long> a(num.size());
    std::vector<long long> b(mul.size());

    int zeros = 0;
    bool count = true;
    for (int i = num.size()-1; i >= 0; --i) {
        a[i] = num[i] - '0';
        if (a[i]) count = false;
        if (!a[i]) zeros += count;
    }

    count = true;
    for (int i = mul.size()-1; i >= 0; --i) {
        b[i] = mul[i] - '0';
        if (b[i]) count = false;
        if (!b[i]) zeros += count;
    }

    std::vector<long long> answer = FFT::multiply(a, b);
    std::string res;

    int curr = 0, j = answer.size()-1;
    while (j >= 0 || curr) {
        if (j >= 0) curr += answer[j--];
        res += (curr % 10) + '0';
        curr /= 10;
    }

    if (res == "0") return res;
    swap_str(res);

    while (zeros-- > 0) res += '0';
    return res;
}



BigInt::BigInt(std::string number) {
    if (number.empty() || m_number == "-0") {
        m_positive = true;
        m_number = "0";
        return;
    }

    int i = 0;
    m_positive = number[i] != '-';
    if (number[i] == '-' || number[i] == '+')
        ++i;

    while (i < number.size()) {
        if (!isdigit(number[i])) {
            std::cerr << number;
            throw std::runtime_error("Incorrect number");
        }
        m_number += number[i++];
    }
}

std::string BigInt::binary() const {
    std::string res = bin(m_number);
    if (m_positive) {
        swap_str(res);
        return "0" + res;
    }

    // for negative numbers inverse all bits and add 1
    bool add = true;
    for (int i = 0; i < res.size(); ++i) {
        if (add) add = res[i] == '0';
        else res[i] = res[i] == '1' ? '0' : '1';
    }

    res += '1';
    swap_str(res);
    return res;
}

BigInt BigInt::pow(const BigInt &step) const {
    if (m_number == "0" && step.m_number == "0") throw std::runtime_error("0.pow(0) error");
    if (m_number == "1" || step.m_number == "0") return {1};
    if (m_number == "0" || !step.m_positive) return {0};
    std::string bits = bin(step.m_number);

    BigInt res(1), curr(*this);
    for (int i = 0; i < bits.size(); ++i) {
        if (bits[i] == '1') {
            res = res * curr;
            // std::cout << res.m_number.size() << std::endl;
        }
        curr = curr * curr;
    }
    return res;
}



BigInt BigInt::operator+(const BigInt &num) const {
    if (m_positive && num.m_positive) return {add(m_number, num.m_number)};
    if (!m_positive && !num.m_positive) return {"-" + add(m_number, num.m_number)};

    Comparison res = compare(m_number, num.m_number);
    if (res == LBIGGER) return {(m_positive ? "" : "-") + subtract(m_number, num.m_number)};
    if (res == RBIGGER) return {(num.m_positive ? "" : "-") + subtract(num.m_number, m_number)};
    return {0};
}

BigInt BigInt::operator-(const BigInt &num) const {
    if (m_positive && !num.m_positive) return {add(m_number, num.m_number)};
    if (!m_positive && num.m_positive) return {"-" + add(m_number, num.m_number)};

    Comparison res = compare(m_number, num.m_number);
    if (res == LBIGGER) return {(m_positive ? "" : "-") + subtract(m_number, num.m_number)};
    if (res == RBIGGER) return {(num.m_positive ? "-" : "") + subtract(num.m_number, m_number)};
    return {0};
}

BigInt BigInt::operator*(const BigInt &num) const {
    std::string sign = (m_positive && num.m_positive || !m_positive && !num.m_positive) ? "" : "-";
    if (m_number.size() + num.m_number.size() < 10000) return {sign + karatsuba_mult(m_number, num.m_number)};
    return {sign + fft_mult(m_number, num.m_number) };
}


BigInt BigInt::operator/(const BigInt &num) const {
    std::string sign = (m_positive && num.m_positive || !m_positive && !num.m_positive) ? "" : "-";
    std::string res = BigInt::divide(m_number, num.m_number, false);
    return res.empty() ? BigInt(0) : BigInt(sign + res);
}

BigInt BigInt::operator%(const BigInt &num) const {
    std::string sign = m_positive ? "" : "-";
    std::string res = BigInt::divide(m_number, num.m_number, true);
    return res.empty() ? BigInt(0) : BigInt(sign + res);
}



bool BigInt::operator<(const BigInt &num) const {
    if (!m_positive && num.m_positive) return true;
    if (m_positive && !num.m_positive) return false;

    Comparison res = compare(m_number, num.m_number);
    return m_positive && res == RBIGGER || !m_positive && res == LBIGGER;
}
bool BigInt::operator>(const BigInt &num) const {
    if (!m_positive && num.m_positive) return false;
    if (m_positive && !num.m_positive) return true;

    Comparison res = compare(m_number, num.m_number);
    return m_positive && res == LBIGGER || !m_positive && res == RBIGGER;
}

bool BigInt::operator<=(const BigInt &num) const { return !(*this > num); }
bool BigInt::operator>=(const BigInt &num) const { return !(*this < num); }

bool BigInt::operator==(const BigInt &num) const {
    if (m_positive != num.m_positive) return false;
    return compare(m_number, num.m_number) == EQUAL;
}

BigInt::operator int() const {
    std::string res = binary();
    const int size = res.size();
    int num = 0;

    if (size >= 32 && res[size-32] == '1')
        num |= 1 << 31;

    for (int i = std::max(0, (int)res.size()-31), j = std::min(30, (int)res.size()-1); i < res.size(); ++i, --j)
        if (res[i] == '1')
            num |= 1 << j;
    return num;
}

BigInt::operator std::string() const {
    return (m_positive ? "" : "-") + m_number;
}
