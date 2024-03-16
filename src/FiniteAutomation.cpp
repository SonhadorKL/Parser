#include "FiniteAutomation.hpp"
#include <set>
#include <string>
#include <queue>
#include <iostream>

using Aut::FiniteAutomation;
using Automation = Aut::FiniteAutomation; 

Automation Aut::ConcatenateAut(FiniteAutomation aut1, FiniteAutomation aut2) {

    if (aut1.GetEndNode()->number > aut2.GetEndNode()->number) {
        std::swap(aut1.GetEndNode()->number, aut2.GetEndNode()->number);
    }
    auto& transitions = aut1.GetEndNode()->state_fuction[Aut::kEpsilon];
    transitions.push_front(aut2.GetStartNode());
    
    aut1.GetEndNode()->is_terminal = false;
    aut1.SetEndNode(aut2.GetEndNode());

    return aut1;
}

FiniteAutomation Aut::UnionAut(FiniteAutomation aut1, FiniteAutomation aut2) {

    size_t unused_num = std::max(aut1.GetEndNode()->number, aut2.GetEndNode()->number) + 1;
    // Create start state for aut
    Aut::NodePtr start_state(std::make_shared<Node>());
    start_state->number = unused_num++;
    start_state->is_terminal = false;
    auto& start_transitions = start_state->state_fuction[kEpsilon];
    start_transitions.push_front(aut1.GetStartNode());
    start_transitions.push_front(aut2.GetStartNode());

    // Create end state for aut
    Aut::NodePtr end_state(std::make_shared<Node>());
    end_state->number = unused_num++;
    end_state->is_terminal = true;
    auto& aut1_trans = aut1.GetEndNode()->state_fuction[kEpsilon];
    auto& aut2_trans = aut2.GetEndNode()->state_fuction[kEpsilon];
    aut1_trans.push_front(end_state);
    aut2_trans.push_front(end_state);
    aut1.GetEndNode()->is_terminal = false;
    aut2.GetEndNode()->is_terminal = false;

    return Automation(start_state, end_state);;
}

FiniteAutomation Aut::KleenStarAut(FiniteAutomation aut) {
    size_t unused_num = aut.GetEndNode()->number + 1;
    
    // Create start state for aut
    Aut::NodePtr start_end_state(std::make_shared<Node>());
    start_end_state->number = unused_num++;
    start_end_state->is_terminal = true;
    auto& start_transitions = start_end_state->state_fuction[kEpsilon];
    start_transitions.push_front(aut.GetStartNode());

    auto& prev_end_trans = aut.GetEndNode()->state_fuction[kEpsilon];
    prev_end_trans.push_front(start_end_state);
    aut.GetEndNode()->is_terminal = false;

    return Automation(start_end_state, start_end_state);
}

Aut::FiniteAutomation::FiniteAutomation(NodePtr start_node, NodePtr end_node) : start_node_(start_node), end_node_(end_node) {}
Aut::FiniteAutomation::FiniteAutomation(char symbol, size_t unused_num) :
            start_node_(std::make_shared<Node>()), end_node_(std::make_shared<Node>()) {
    start_node_->number = unused_num++; 
    start_node_->is_terminal = false;
    auto& start_trans = start_node_->state_fuction[symbol];
    start_trans.push_front(end_node_);
    
    end_node_->is_terminal = true;
    end_node_->number = unused_num++;
}

size_t Aut::FiniteAutomation::GetUsedNum() {
    return end_node_->number;
}

Aut::NodePtr Aut::FiniteAutomation::GetStartNode() {
    return start_node_;
}

Aut::NodePtr Aut::FiniteAutomation::GetEndNode() {
    return end_node_;
}

void Aut::FiniteAutomation::SetEndNode(NodePtr new_end_nod) {
    end_node_ = new_end_nod;
}
