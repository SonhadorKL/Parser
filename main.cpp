#include <iostream>
#include "RegularExpression.hpp"
#include <queue>

int main() {
    std::string regex;
    std::cout << "Regex in reverse polish notation: ";
    std::cin >> regex;
    Aut::FiniteAutomation automate_from_regex = Aut::RegularToAutomation(regex);

    std::string str_to_search;
    std::cout << "String to search maximum prefix: ";
    std::cin >> str_to_search;
    Aut::SearchInAutomation solver(automate_from_regex, str_to_search);

    std::cout << "The length of maximum prefix which is a prefix of word from given regex: "
              << solver.GetMaxPref() << '\n';
    return 0;
}