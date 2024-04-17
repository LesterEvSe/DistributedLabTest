#include "CSVHandler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// Hash Tables
#include <unordered_map>
#include <unordered_set>


std::pair<ll, ll> CSVHandler::process_line(const std::string &line) {
    ll user_id = 0, product_id = 0;
    int i = 0;

    while (line[i] != ',')
        user_id = user_id*10 + line[i++] - '0';

    while (line[++i] != ',')
        product_id = product_id*10 + line[i] - '0';

    return {user_id, product_id};
}

CSVHandler::CSVHandler(const std::string &data1, const std::string data2)
{
    // The key is the user's id, and the value is the products visited by this user
    std::unordered_map<ll, std::unordered_set<ll>> day1;
    std::ifstream file1(data1);
    std::string line;

    // skip first line with names
    std::getline(file1, line);

    while (std::getline(file1, line)) {
        std::pair<ll, ll> user_prod = process_line(line);
        //std::cout << user_prod.first << ' ' << user_prod.second << std::endl;
        day1[user_prod.first].emplace(user_prod.second);
    }

    std::ifstream file2(data2);
    std::getline(file2, line);

    // To check for duplicates
    std::unordered_set<ll> in_answer;

    while (std::getline(file2, line)) {
        std::pair<ll, ll> temp = process_line(line);
        ll user = temp.first;
        ll prod = temp.second;

        if (!in_answer.count(user) && day1.count(user) && !day1[user].count(prod)) {
            m_answer.emplace_back(user);
            in_answer.emplace(user);
        }
    }
}

void CSVHandler::print_answer() const {
    std::cout << "\nThe IDs of the users who visited some pages on both days and\n";
    std::cout << "who on the second day visited the page that hadn't been visited by this user on the first day:\n";

    for (ll elem : m_answer)
        std::cout << elem << ' ';
    std::cout << std::endl << std::endl;
}
