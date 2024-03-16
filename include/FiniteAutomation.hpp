#pragma once

#include <memory>
#include <list>
#include <unordered_map>

namespace Aut {
    struct Node;    
    using NodePtr = std::shared_ptr<Node>;

    // Symbol which is considered as empty word
    const char kEpsilon = '1';

    // Represent one state of of automat 
    struct Node {
       size_t number;
       std::unordered_map<char, std::list<NodePtr>> state_fuction;
       bool is_terminal;
    };

    
    class FiniteAutomation {
      private:
        NodePtr start_node_;
        // Guaranteed that number of end_node_ is maximum
        NodePtr end_node_;

      public:
        FiniteAutomation() = default;
        FiniteAutomation(NodePtr start_node, NodePtr end_node);
        
        // Parameter num show which numbers can be used as numbers of Nodes
        FiniteAutomation(char symbol, size_t num);
        
        // Get the maximum number of nodes 
        size_t GetUsedNum();

        NodePtr GetStartNode();
        NodePtr GetEndNode();

        void SetEndNode(NodePtr new_end_nod);
    };

    // Functions to operate with automations
    
    // Using aut1 and aut2 after calling this functions is UB
    FiniteAutomation ConcatenateAut(FiniteAutomation aut1, FiniteAutomation aut2);
    // Using aut1 and aut2 after calling this functions is UB
    FiniteAutomation UnionAut(FiniteAutomation aut1, FiniteAutomation aut2);
    // Using aut after calling this functions is UB
    FiniteAutomation KleenStarAut(FiniteAutomation aut);
}