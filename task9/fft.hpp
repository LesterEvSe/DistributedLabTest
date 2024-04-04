#ifndef LONGARITH_FFT_HPP
#define LONGARITH_FFT_HPP

#include <vector>
#include <complex>

// Reworked code from http://web.mit.edu/~ecprice/acm/acm08/notebook.html#file12
class FFT {
private:
    using reim = std::complex<double>;

    const short bits;
    const size_t n;

    std::vector<long long> m_rev;
    std::vector<reim> m_data, m_roots;

    // Set size func
    FFT(const std::vector<long long> &nums, short _bits);
    void transform(bool inverse);

    void operator*=(const FFT &nums);
    const std::vector<reim> &data() const;

public:
    static std::vector<long long> multiply(const std::vector<long long> &a, const std::vector<long long> &b);
};

#endif //LONGARITH_FFT_HPP
