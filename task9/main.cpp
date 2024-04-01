#include <iostream>
#include "BigInt.hpp"

#include <vector>
#include <complex>
#include <cstdlib>
#include <ctime>
#include <cmath>

class FFTM
{
private:
    using reim = std::complex<double>;

    std::vector<reim> data, roots;
    std::vector<int> rev;
    int s, n;

    void setSize(int ns)
    {
        s = ns;
        n = (1 << s);
        rev = std::vector<int>(n);
        data = std::vector<reim> (n);
        roots = std::vector<reim> (n + 1);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < s; ++j) {
                if (!(i & (1 << j))) continue;
                rev[i] += (1 << (s - j - 1));
            }

        const double x = 2 * M_PI / n;
        reim mult = reim(cos(x), sin(x));

        roots[0] = reim(1, 0);
        for (int i = 1; i <= n; ++i)
            roots[i] = roots[i-1] * mult;
    }

    void bitReverse(std::vector<reim> &array)
    {
        std::vector<reim> temp(n);
        for (int i = 0; i < n; ++i) temp[i] = array[rev[i]];
        for (int i = 0; i < n; ++i) array[i] = temp[i];
    }

    void transform(bool inverse = false)
    {
        bitReverse(data);
        for (int i = 1; i <= s; ++i) {
            int m = (1 << i), md2 = m / 2;
            int start = 0, increment = (1 << (s-i));
            if (inverse) {
                start = n;
                increment *= -1;
            }

            for (int k = 0; k < n; k += m) {
                int index = start;
                for (int j = k; j < md2+k; ++j) {
                    reim t = roots[index] * data[j+md2];
                    index += increment;
                    data[j+md2] = data[j] - t;
                    data[j] = data[j] + t;
                }
            }
        }

        if (!inverse) return;
        for (int i = 0; i < n; ++i)
            data[i] /= n;
    }

public:
    static std::vector<int> multiply(const std::vector<int> &a, const std::vector<int> &b)
    {
        int alen = a.size(), blen = b.size();
        int resn = alen + blen - 1;	// size of the resulting array
        int s = 0;
        while ((1 << s) < resn) s++;	// n = 2^s
        int n = 1 << s;	// round up the the nearest power of two

        FFTM pga, pgb;
        pga.setSize(s);	// fill and transform first array
        for (int i = 0; i < alen; i++) pga.data[i] = reim(a[i], 0);
        for (int i = alen; i < n; i++) pga.data[i] = reim(0, 0);
        pga.transform();

        pgb.setSize(s);	// fill and transform second array
        for (int i = 0; i < blen; i++) pgb.data[i] = reim(b[i], 0);
        for (int i = blen; i < n; i++) pgb.data[i] = reim(0, 0);
        pgb.transform();

        for (int i = 0; i < n; i++)	pga.data[i] = pga.data[i] * pgb.data[i];
        pga.transform(true);	// inverse transform
        std::vector<int> result = std::vector<int> (resn);	// round to nearest integer
        for (int i = 0; i < resn; i++)
            result[i] = round(pga.data[i].real());

        int actualSize = resn - 1;	// find proper size of array
        while (result[actualSize] == 0)
            --actualSize;

        if (actualSize < 0) actualSize = 0;
        result.resize(actualSize+1);
        return result;
    }
};

#include "fft.hpp"

int main()
{
    std::vector<int> a = std::vector<int> {3, 9, 4, 2};
    std::vector<int> b = std::vector<int> {7, 3, 9, 0};
    std::vector<int> c = FFTM::multiply(a, b);

    for (int num : c)
        std::cout << num << ' ';
    std::cout << std::endl;

    //std::string as = "3942";
    //std::string bs = "7390";
    for (int num : FFT::multiply(a, b))
        std::cout << num << ' ';
    return 0;
}


/*
const int LEN = 4 * 2;

using reim = std::ccomplex<double>;
using vecreim = std::vector<reim>;

void all_fft(vecreim& mass, bool reverse) {
    int n = mass.size();
    if (n == 1)  return;

    vecreim A(n / 2);
    vecreim B(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        A[i] = mass[2 * i];
        B[i] = mass[2 * i + 1];
    }

    all_fft(A, reverse);
    all_fft(B, reverse);

    double a = 2 * M_PI / n * (reverse ? -1 : 1);
    reim w = { 1, 0 };
    reim w1 = { cos(a), sin(a) };

    for (int i = 0; i < n / 2; ++i) {
        mass[i] = A[i] + w * B[i];
        mass[i + n / 2] = A[i] - w * B[i];
        if (reverse) mass[i] /= 2, mass[i + n / 2] /= 2;
        w *= w1;
    }
}


void print_mass(vecreim& mass) {
    for (int i = LEN/2 - 1; i >= 0; --i)
        std::cout << mass[i].real() << "x**" << i << ' ';
    std::cout << std::endl;
}

void mass_gen(vecreim& mass) {
    for (int i = 0; i < LEN/2; ++i)
        mass[i] = rand() % 10;
}

void dft(vecreim& a, vecreim& b, vecreim& c)
{
    for (int i = 0; i < LEN - 1; ++i)
        for (int j = 0; j <= i; ++j)
            c[i] += (a[j] * b[i - j]);
}

int main()
{
    long double average_time = 0;

    for (int i = 0; i < 100; ++i)
    {
        vecreim mass1(LEN);
        vecreim mass2(LEN);
        vecreim mass3(LEN);

        srand(i);
        mass_gen(mass1);
        mass_gen(mass2);


        if (i == 99) {
            print_mass(mass1);
            print_mass(mass2);
        }


        unsigned long start_pos = clock();
        dft(mass1, mass2, mass3);
        unsigned long end_pos = clock();

        average_time += (end_pos - start_pos) / 1000.0;

        start_pos = clock();
        all_fft(mass1, 0);
        all_fft(mass2, 0);
        for (int i = 0; i < LEN; ++i)
            mass3[i] = mass1[i] * mass2[i];
        all_fft(mass3, 1);
        end_pos = clock();

        average_time += (end_pos - start_pos) / 1000.0;


        if (LEN > 4) {
            unsigned long start_pos = clock();
            all_fft(mass1, 0);
            all_fft(mass2, 0);
            for (int i = 0; i < LEN; ++i) mass3[i] = mass1[i] * mass2[i];
            all_fft(mass3, 1);
            unsigned long end_pos = clock();

            average_time += (end_pos - start_pos) / 1000.0;
        }
        else {
            unsigned long start_pos = clock();
            dft(mass1, mass2, mass3);
            unsigned long end_pos = clock();

            average_time += (end_pos - start_pos) / 1000.0;
        }


        if (i != 99) continue;
        for (int i = LEN - 2; i > -1; --i)
            std::cout << mass3[i].real() << "x**" << i << ' ';
    }


    std::cout << "\nAverage tim for 100 iterations: " << average_time / 100 << " sec" << '\n';
    return 0;
}
*/



/*

// Using test from https://raw.githubusercontent.com/microsoft/rego-cpp/main/tests/bigint.yaml
std::string check(BigInt actual, BigInt expected) {
    return std::string(actual == expected ? "true" : "false") + "\n";
}

void plus_and_minus_tests() {
    BigInt num1, num2;
    num1 = -2;
    num2 = -15;
    std::cout << "Test1: " << check(num1 + num2, BigInt(-17));

    num1 = BigInt(-3796);
    num2 = BigInt(4047);
    std::cout << "Test2: " << check(num1 + num2, BigInt(251));

    num1 = BigInt(-253534);
    num2 = BigInt(-214311);
    std::cout << "Test3: " << check(num1 + num2, BigInt(-467845));

    num1 = BigInt("187224985");
    num2 = BigInt("235111630");
    std::cout << "Test4: " << check(num1 + num2, BigInt("422336615"));

    num1 = BigInt();
    num2 = BigInt(12124);
    std::cout << "Test5: " << check(num1 + num2, num2);

    num1 = BigInt("6466055601279126416241593829827225642974873054416615134420424370024610277048");
    num2 = BigInt("812377893613439962506223192889271172721150454313527119829598533028254192660");
    std::cout << "Test6: " << check(num1 + num2, BigInt("7278433494892566378747817022716496815696023508730142254250022903052864469708"));

    // subtract Test
    num1 = BigInt(-1);
    num2 = BigInt(11);
    std::cout << "Test7: " << check(num1 - num2, BigInt(-12));

    num1 = BigInt(2527);
    num2 = BigInt(-1226);
    std::cout << "Test8: " << check(num1 - num2, BigInt(3753));

    num1 = BigInt(-316587);
    num2 = BigInt(-767603);
    std::cout << "Test9: " << check(num1 - num2, BigInt(451016));

    num1 = BigInt("-5912796750055159349348285095168029999547805837934919256759875720338049163859");
    num2 = BigInt("2100436268304949465469152169050553499388589256398614019764087298232731952205");
    std::cout << "Test10: " << check(num1 - num2, BigInt("-8013233018360108814817437264218583498936395094333533276523963018570781116064"));
}

int main() {
    plus_and_minus_tests();
    return 0;
}
*/