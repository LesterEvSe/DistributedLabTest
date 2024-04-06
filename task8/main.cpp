#include <iostream>
#include <sstream>
#include <stdexcept>

#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using ll = long long;


ll max_student_capital(ll N, ll C, const std::vector<ll> &gains, const std::vector<ll> &price)
{
    const size_t n = gains.size();
    if (n != price.size()) throw std::runtime_error("Different lengths of arrays\n");

    std::vector<std::pair<ll, ll>> vecpair(n);
    // calculate pure profit here
    for (size_t i = 0; i < n; ++i)
        vecpair[i] = {price[i], gains[i] - price[i]};
    std::sort(vecpair.begin(), vecpair.end());

    // Store profits
    std::priority_queue<ll> pq;
    size_t i = 0;
    ll capital = C;

    while (N-- > 0) {
        while (i < n && vecpair[i].first <= C)
            pq.emplace(vecpair[i++].second);

        if (pq.empty() || pq.top() <= 0)
            break;

        C += pq.top();
        pq.pop();
    }
    return C;
}

std::vector<ll> get_arr(std::string text) {
    std::vector<ll> arr;
    std::cout << text << "\n";

    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);

    ll num;
    while (iss >> num)
        arr.emplace_back(num);
    return arr;
}


int main() {
    ll N, C;
    std::cout << "Enter the number of laptops: ";
    std::cin >> N;

    std::cout << "Enter your starting capital: ";
    std::cin >> C;
    std::cin.ignore(); // clear '\n' symbol

    std::vector<ll> gains = get_arr("Enter gains array separated by spaces (press Enter to stop):");
    std::vector<ll> price = get_arr("Enter price array separated by spaces (press Enter to stop):");

    std::cout << "Capital at the end of summer = " << max_student_capital(N, C, gains, price);

    std::cout << std::endl;
    return 0;
}
