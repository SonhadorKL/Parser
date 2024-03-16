#include "RegularExpression.hpp"    
#include <gtest/gtest.h>

TEST(RegexTest, InvalidRegex) {
    EXPECT_THROW(Aut::RegularToAutomation("a+"), std::invalid_argument);
    EXPECT_THROW(Aut::RegularToAutomation("abc+"), std::invalid_argument);
    EXPECT_THROW(Aut::RegularToAutomation("qqqq"), std::invalid_argument);
}

TEST(RegexTest, Correctness) {
    // a(a+b)(c)*
    Aut::FiniteAutomation aut1 = Aut::RegularToAutomation("aab+.c*.");
    
    Aut::SearchInAutomation checker11(aut1, "abccccccc");
    EXPECT_TRUE(checker11.CheckIfAcceptWord(aut1.GetStartNode(), 0));

    Aut::SearchInAutomation checker12(aut1, "aa");
    EXPECT_TRUE(checker12.CheckIfAcceptWord(aut1.GetStartNode(), 0));

    Aut::SearchInAutomation checker13(aut1, "abb");
    EXPECT_FALSE(checker13.CheckIfAcceptWord(aut1.GetStartNode(), 0));
}

TEST(RegexTest, WithEpsilon) {
    // (aaa)*
    Aut::FiniteAutomation aut1 = Aut::RegularToAutomation("1*aa.a.*.1.");
    
    Aut::SearchInAutomation checker11(aut1, "aaaaaa");
    EXPECT_TRUE(checker11.CheckIfAcceptWord(aut1.GetStartNode(), 0));

    Aut::SearchInAutomation checker12(aut1, "aaaa");
    EXPECT_FALSE(checker12.CheckIfAcceptWord(aut1.GetStartNode(), 0));

    Aut::SearchInAutomation checker13(aut1, "11a1a1a");
    EXPECT_TRUE(checker13.CheckIfAcceptWord(aut1.GetStartNode(), 0));
}

TEST(Algorithm, Correctness) {
    EXPECT_EQ(Aut::GetMaxPref("aa.a.bb.b..", "aabbcc"), 2);
    EXPECT_EQ(Aut::GetMaxPref("a*b*.", "aaaab"), 5);
    EXPECT_EQ(Aut::GetMaxPref("a*b*.", "bbbbaaa"), 4);
    EXPECT_EQ(Aut::GetMaxPref("ab+c+*", "bcbcbc"), 6);
    EXPECT_EQ(Aut::GetMaxPref("ab.*", "ababac"), 5);

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}