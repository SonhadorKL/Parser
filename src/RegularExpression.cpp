#include "RegularExpression.hpp"
#include <stack>
#include <iostream>
#include <string>
#include <stdexcept>

const char kUnionSym = '+';
const char kKleenSym = '*';
const char kConcatenateSym = '.';

const size_t kAlphSize = 7;
const char kAlphabet[kAlphSize] = {'1', 'a', 'b', 'c', '+', '*', '.'};

bool inAlphabet(char ch) {
    bool is_in = false;
    for (size_t i = 0; i < kAlphSize; ++i) {
        is_in = is_in || (kAlphabet[i] == ch);
    }
    return is_in;
}

// The function to throw exception if doesn't have enough elements to operate automats
void CheckAvailableCount(size_t aut_count, size_t needed, char oper) {
    if (aut_count < needed) {
        throw std::invalid_argument(
            std::string(R"(
            Regular expression is invalid:
            there is not enough operands for operator )") + oper);
    }
}

// The function to throw exception if final result is ambiguous
void CheckFinalAut(size_t aut_count) {
    if (aut_count > 1) {
        throw std::invalid_argument(
            std::string(R"(
            Regular expression is invalid:
            does not have enough operators)"));
    }
}

// The function to throw exception if regular expr have wrong char
void CheckInvalidChar(char ch) {
    if (!inAlphabet(ch)) {
        throw std::invalid_argument(std::string(R"(
            Regular expression is invalid:
            it has wrong char: )") + ch);
    }
}


Aut::FiniteAutomation Aut::RegularToAutomation(const std::string& reqular) {
    std::stack<FiniteAutomation> auts;
    size_t cur_pos = 0;
    for (const char& ch : reqular) {
        CheckInvalidChar(ch);
        FiniteAutomation aut1, aut2, result;
        if (ch == kUnionSym) {
            CheckAvailableCount(auts.size(), 2, ch);
            aut2 = auts.top(); auts.pop();
            aut1 = auts.top(); auts.pop();
            result = UnionAut(aut1, aut2); 
        } else if (ch == kConcatenateSym) {
            CheckAvailableCount(auts.size(), 2, ch);
            aut2 = auts.top(); auts.pop();
            aut1 = auts.top(); auts.pop();
            result = ConcatenateAut(aut1, aut2); 
        } else if (ch == kKleenSym) {
            CheckAvailableCount(auts.size(), 1, ch);
            aut1 = auts.top(); auts.pop();
            result = KleenStarAut(aut1); 
        } else {
            result = FiniteAutomation(ch, cur_pos++);  
        }
        auts.push(result);
        cur_pos = result.GetUsedNum() + 1;
    }
    CheckFinalAut(auts.size());
    return auts.top();
}

bool Aut::SearchInAutomation::CheckIfAcceptWord(NodePtr cur_node, size_t pos_in_str) {
    max_depth = std::max(pos_in_str, max_depth);
    if (cur_node->is_terminal && pos_in_str == str_to_search_.size()) {
        return true;
    }
    // DFS went in cycle which did not change word, so we don't need to check it
    if (used_.at(cur_node->number) == pos_in_str) {
        return false;
    }

    used_.at(cur_node->number) = pos_in_str;
    auto& state_func = cur_node->state_fuction; 

    bool is_reachable = false;
    // Case if DFS went on all letters so next it should go only on empty-letters
    size_t word_is_full = (pos_in_str == str_to_search_.size() ? 1 : 0);
    for (size_t i = word_is_full; i < 2; ++i) {
        char target_ch = (i == 0 ? str_to_search_.at(pos_in_str) : Aut::kEpsilon);
        size_t next_pos = (i == 0 ? pos_in_str + 1 : pos_in_str);
        if (state_func.find(target_ch) != state_func.end()) {
            for (NodePtr next_node : state_func[target_ch]) {
                is_reachable = is_reachable || CheckIfAcceptWord(next_node, next_pos);
                used_.at(cur_node->number) = pos_in_str;
                if (is_reachable) {
                    break;
                }
            }
        }
    }
    used_.at(cur_node->number) = 0;
    return is_reachable;
}


Aut::SearchInAutomation::SearchInAutomation(FiniteAutomation aut, std::string str) :
    aut_(aut), used_(aut_.GetUsedNum() + 1, -1) {
        for (const auto& ch : str) {
            if (ch != Aut::kEpsilon) {
                str_to_search_ += ch;
            }
        }
}

size_t Aut::SearchInAutomation::GetMaxPref() {
    CheckIfAcceptWord(aut_.GetStartNode(), 0);
    return max_depth;
}

size_t Aut::GetMaxPref(std::string regex, std::string str) {
    FiniteAutomation aut = RegularToAutomation(regex);
    SearchInAutomation checker(aut, str);
    
    return checker.GetMaxPref();
}
