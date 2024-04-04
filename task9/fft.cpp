#include "fft.hpp"
#include <cmath> // For M_PI constant

FFT::FFT(const std::vector<long long> &nums, short _bits):
    bits(_bits), n(1LL << bits), m_rev(n), m_data(n), m_roots(n+1)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < bits; ++j) {
            if (!(i & (1 << j))) continue;
            m_rev[i] += (1 << (bits - j - 1));
        }

    const double x = 2 * M_PI / n;
    reim multiplier(cos(x), sin(x));

    m_roots[0] = reim(1, 0);
    for (int i = 0; i < n; ++i)
        m_roots[i+1] = m_roots[i] * multiplier;

    for (long long i = 0; i < nums.size(); ++i)
        m_data[i] = reim(nums[i], 0);
}

void FFT::transform(bool inverse)
{
    // Reverse m_data bits
    std::vector<reim> temp(n);
    for (int i = 0; i < n; ++i) temp[i] = m_data[m_rev[i]];
    for (int i = 0; i < n; ++i) m_data[i] = temp[i];

    for (int i = 1; i <= bits; ++i){
        int m = (1 << i), md2 = m >> 1;
        size_t start = 0, inc = (1 << (bits-i));

        if (inverse) {
            start = n;
            inc *= -1;
        }

        for (int k = 0; k < n; k += m) {
            size_t ind = start;

            for (int j = k; j < md2+k; ++j) {
                reim t = m_roots[ind] * m_data[j + md2];
                ind += inc;
                m_data[j + md2] = m_data[j] - t;
                m_data[j] = m_data[j] + t;
            }
        }
    }

    if (!inverse) return;
    for (int i = 0; i < n; ++i)
        m_data[i] /= n;
}

void FFT::operator*=(const FFT &nums) {
    for (int i = 0; i < n; ++i)
        m_data[i] *= nums.m_data[i];
}

const std::vector<FFT::reim> &FFT::data() const {
    return m_data;
}


std::vector<long long> FFT::multiply(const std::vector<long long> &a, const std::vector<long long> &b)
{
    const size_t alen = a.size(), blen = b.size();
    const size_t resn = alen + blen - 1;
    short bits = 0;

    while ((1 << bits) < resn)
        ++bits;

    FFT A(a, bits), B(b, bits);
    A.transform(false);
    B.transform(false);
    A *= B; // Dot multiplication
    A.transform(true);

    const std::vector<reim> &data = A.data();
    std::vector<long long> res(resn);

    for (int i = 0; i < resn; ++i)
        res[i] = round(data[i].real());

    int actual = resn-1;
    while (actual >= 0 && res[actual] == 0)
        --actual;

    if (actual < 0) actual = 0;
    res.resize(actual + 1);
    return res;
}