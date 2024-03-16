#pragma once

#include "FiniteAutomation.hpp"
#include <vector>
#include <string>

namespace Aut {
    // Converts a regular expression in reverse Polish notation into an autormat
    FiniteAutomation RegularToAutomation(const std::string& regular);

    class SearchInAutomation {
      private:
        FiniteAutomation aut_;
        std::string str_to_search_;

        // used_[i] show with which length of prefix algorithm was in given state
        std::vector<size_t> used_;
        
        size_t max_depth = 0;

      public:
        // Run DFS from one vert to check if it reaches end
        // In process it counts len of max prefix which is in automat
        bool CheckIfAcceptWord(NodePtr cur_node, size_t pos_in_str);
        
        SearchInAutomation(FiniteAutomation aut, std::string str);

        size_t GetMaxPref();
    };

    // To get maximum prefix in one function
    size_t GetMaxPref(std::string regex, std::string str);
}