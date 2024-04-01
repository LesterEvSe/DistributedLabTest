#include "BigInt.hpp"
#include <stdexcept>




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

    for (i = 0, j = answer.size()-1; i < j; ++i, --j)
        std::swap(answer[i], answer[j]);
    return answer;
}

// Assume that num will always be less than minus
std::string BigInt::subtract(const std::string &num, const std::string &minus) {
    std::string answer;
    int curr = 0, i = num.size()-1, j = minus.size()-1;

    while (j >= 0 || curr) {
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

    for (i = 0, j = answer.size()-1; i < j; ++i, --j)
        std::swap(answer[i], answer[j]);
    return answer;
}

BigInt::Comparison BigInt::compare(const std::string &num1, const std::string &num2) {
    if (num1.size() != num2.size()) return num1.size() < num2.size() ? LBIGGER : RBIGGER;
    for (int i = 0; i < num1.size(); ++i) {
        if (num1[i] > num2[i]) return LBIGGER;
        else if (num1[i] < num2[i]) return RBIGGER;
    }
    return EQUAL;
}


BigInt::BigInt(std::string number) {
    if (number.empty()) {
        m_positive = true;
        m_number = "0";
        return;
    }

    int i = 0;
    m_positive = number[i] != '-';
    if (number[i] == '-' || number[i] == '+')
        ++i;

    while (i < number.size()) {
        if (!isdigit(number[i]))
            throw std::runtime_error("Incorrect number");
        m_number += number[i++];
    }
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
    return {0};
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


// Todo convert here to 31 bit number and add sign
BigInt::operator int() const {
    return std::stoi(m_number);
}
BigInt::operator std::string() const {
    return (m_positive ? "" : "-") + m_number;
}