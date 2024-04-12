#ifndef CSV_HANDLER_HPP
#define CSV_HANDLER_HPP

#include <vector>
#include <string>
using ll = long long;


class CSVHandler {
private:
    std::vector<ll> m_first_answer;
    std::vector<ll> m_second_answer;

    std::pair<ll, ll> process_line(const std::string &line);

public:
    CSVHandler(const std::string &data1, const std::string data2);
    void print_answers() const;
};

#endif //CSV_HANDLER_HPP
