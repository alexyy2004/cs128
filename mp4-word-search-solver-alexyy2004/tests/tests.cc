// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("Horizontal", "[horizontal]") {
    std::vector<std::vector<char>> puzzle{{'h', 'a', 'l', 'l', 'o'},
                                          {'q', 'a', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'l', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE_FALSE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
    REQUIRE(std::cout << wss.FindWord("hello").char_positions.at(0));
    REQUIRE(wss.FindWord("hello",CheckDirection::kHorizontal).char_positions.at(0).character == 'h');
    REQUIRE(wss.FindWord("hello",CheckDirection::kHorizontal).char_positions.at(0).col == 0);
    REQUIRE(wss.FindWord("hello",CheckDirection::kHorizontal).char_positions.at(0).row == 4);
    REQUIRE(wss.FindWord("hello",CheckDirection::kHorizontal).char_positions.at(4).character == 'o');
    REQUIRE(wss.FindWord("hello",CheckDirection::kHorizontal).char_positions.at(4).col == 4);
    REQUIRE(wss.FindWord("hello",CheckDirection::kHorizontal).char_positions.at(4).row == 4);
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
    REQUIRE_THROWS_AS(wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
}

TEST_CASE("Vertical", "[vertical]") {
    std::vector<std::vector<char>> puzzle{{'h', 'a', 'l', 'l', 'o'},
                                          {'e', 'a', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'l', 'u'},
                                          {'o', 'a', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE_FALSE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
    REQUIRE(std::cout << wss.FindWord("hello").char_positions.at(0));
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
    REQUIRE(wss.FindWord("hello",CheckDirection::kVertical).char_positions.at(0).character == 'h');
    REQUIRE(wss.FindWord("hello",CheckDirection::kVertical).char_positions.at(0).col == 0);
    REQUIRE(wss.FindWord("hello",CheckDirection::kVertical).char_positions.at(0).row == 0);
    REQUIRE(wss.FindWord("hello",CheckDirection::kVertical).char_positions.at(4).character == 'o');
    REQUIRE(wss.FindWord("hello",CheckDirection::kVertical).char_positions.at(4).col == 0);
    REQUIRE(wss.FindWord("hello",CheckDirection::kVertical).char_positions.at(4).row == 4);
}

TEST_CASE("LeftDiag", "[leftDiag]") {
    std::vector<std::vector<char>> puzzle{{'h', 'a', 'l', 'l', 'h'},
                                          {'a', 'a', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'l', 'u'},
                                          {'o', 'a', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE_FALSE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
    REQUIRE(std::cout << wss.FindWord("hello").char_positions.at(0));
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
    REQUIRE(wss.FindWord("hello",CheckDirection::kLeftDiag).char_positions.at(0).character == 'h');
    REQUIRE(wss.FindWord("hello",CheckDirection::kLeftDiag).char_positions.at(0).col == 4);
    REQUIRE(wss.FindWord("hello",CheckDirection::kLeftDiag).char_positions.at(0).row == 0);
    REQUIRE(wss.FindWord("hello",CheckDirection::kLeftDiag).char_positions.at(4).character == 'o');
    REQUIRE(wss.FindWord("hello",CheckDirection::kLeftDiag).char_positions.at(4).col == 0);
    REQUIRE(wss.FindWord("hello",CheckDirection::kLeftDiag).char_positions.at(4).row == 4);
}

TEST_CASE("RightDiag", "[rightDiag]") {
    std::vector<std::vector<char>> puzzle{{'h', 'a', 'l', 'l', 'o'},
                                          {'a', 'e', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'l', 'u'},
                                          {'o', 'a', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE_FALSE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
    REQUIRE(std::cout << wss.FindWord("hello").char_positions.at(0));
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
    REQUIRE(wss.FindWord("hello",CheckDirection::kRightDiag).char_positions.at(0).character == 'h');
    REQUIRE(wss.FindWord("hello",CheckDirection::kRightDiag).char_positions.at(0).col == 0);
    REQUIRE(wss.FindWord("hello",CheckDirection::kRightDiag).char_positions.at(0).row == 0);
    REQUIRE(wss.FindWord("hello",CheckDirection::kRightDiag).char_positions.at(4).character == 'o');
    REQUIRE(wss.FindWord("hello",CheckDirection::kRightDiag).char_positions.at(4).col == 4);
    REQUIRE(wss.FindWord("hello",CheckDirection::kRightDiag).char_positions.at(4).row == 4);
}

TEST_CASE("Empty", "[empty]") {
    std::vector<std::vector<char>> puzzle{{'h', 'a', 'l', 'l', 'o'},
                                          {'a', 'o', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'l', 'u'},
                                          {'o', 'a', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hello").char_positions.at(0), std::out_of_range);
}

TEST_CASE("two words","[twoWords]") {
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'l', 'l', 'o'},
                                          {'e', 'o', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'l', 'u'},
                                          {'o', 'a', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("hello").word.empty());
    REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
}

TEST_CASE("EmptyWord", "[empty_word]") {
    std::vector<std::vector<char>> puzzle{{'h', 'a', 'l', 'l', 'o'},
                                          {'a', 'o', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'l', 'u'},
                                          {'o', 'a', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);
    REQUIRE(wss.FindWord("", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("").word.empty());
    REQUIRE(wss.FindWord("", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("", CheckDirection::kHorizontal).word.empty());
}
TEST_CASE("wordLongerThanWidth","[WordLongerThanWidth]") {
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'l', 'l', 'o'},
                                          {'e', 'o', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'l', 'u'},
                                          {'o', 'a', 'l', 'l', 'o'}};
    WordSearchSolver wss(puzzle);
    REQUIRE(wss.FindWord("helloo").word.empty());
}

TEST_CASE("right_inverse","[right_inverse]") {
    std::vector<std::vector<char>> puzzle{{'o', 'e', 'l', 'l', 'o'},
                                          {'e', 'l', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'l', 't', 'e', 'u'},
                                          {'o', 'a', 'l', 'l', 'h'}};
    WordSearchSolver wss(puzzle);                                  
    REQUIRE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
}
TEST_CASE("left_inverse","[left_inverse]") {
    std::vector<std::vector<char>> puzzle{{'a', 'e', 'l', 'l', 'o'},
                                          {'e', 'l', 'l', 'l', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'l', 'e', 't', 'e', 'u'},
                                          {'h', 'a', 'l', 'l', 'h'}};
    WordSearchSolver wss(puzzle);                                  
    REQUIRE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
}

TEST_CASE("horizontal_inverse","[horizontal_inverse]") {
    std::vector<std::vector<char>> puzzle{{'o', 'l', 'l', 'e', 'h'},
                                          {'e', 'l', 'l', 'e', 'o'},
                                          {'l', 'a', 's', 'o', 'm'},
                                          {'l', 'l', 't', 'e', 'u'},
                                          {'o', 'a', 'l', 'l', 'h'}};
    WordSearchSolver wss(puzzle);                                  
    REQUIRE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
}
TEST_CASE("vertical_inverse","[vertical_inverse]") {
    std::vector<std::vector<char>> puzzle{{'o', 'e', 'l', 'l', 'o'},
                                          {'l', 'a', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'e', 'l', 't', 'e', 'u'},
                                          {'h', 'a', 'l', 'l', 'h'}};
    WordSearchSolver wss(puzzle);                                  
    REQUIRE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
}

TEST_CASE("EmptyVector", "[empty_vector]") {
    std::vector<std::vector<char>> puzzle{{}};
    WordSearchSolver wss(puzzle);
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello").word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("HELLO", CheckDirection::kVertical).word.empty());
    //REQUIRE(std::cout << wss.FindWord("hello").char_positions.at(0));
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
}

TEST_CASE("horizontal_end","[horizontal_end]") {
    std::vector<std::vector<char>> puzzle{{'o', 'e', 'l', 'l', 'o'},
                                          {'l', 'a', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'e', 'l', 't', 'e', 'u'},
                                          {'h', 'a', 'l', 'l', 'h'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("llo").word.empty());
    REQUIRE_FALSE(wss.FindWord("llo",CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("llo",CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("llo",CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("llo",CheckDirection::kVertical).word.empty());
    REQUIRE(std::cout << wss.FindWord("llo").char_positions.at(0));
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
}

TEST_CASE("vertical_end","[vertical_end]") {
    std::vector<std::vector<char>> puzzle{{'o', 'e', 'l', 'l', 'o'},
                                          {'l', 'a', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'e', 'l', 't', 'e', 'u'},
                                          {'h', 'a', 'l', 'l', 'h'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("uh").word.empty());
    REQUIRE_FALSE(wss.FindWord("uh",CheckDirection::kVertical).word.empty());
    REQUIRE(wss.FindWord("uh",CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("uh",CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("uh",CheckDirection::kHorizontal).word.empty());
    REQUIRE(std::cout << wss.FindWord("uh").char_positions.at(0));
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
}

TEST_CASE("single line", "[single_line]") {
    std::vector<std::vector<char>> puzzle{{'a'},{'b'},{'c'},{'d'},{'e'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("a").word.empty());
    REQUIRE_FALSE(wss.FindWord("b").word.empty());
    REQUIRE_FALSE(wss.FindWord("c").word.empty());
    REQUIRE_FALSE(wss.FindWord("d").word.empty());
    REQUIRE_FALSE(wss.FindWord("e").word.empty());
    REQUIRE_FALSE(wss.FindWord("a",CheckDirection::kHorizontal).word.empty());
    REQUIRE(std::cout << wss.FindWord("a").char_positions.at(0));
    REQUIRE_THROWS_AS(std::cout << wss.FindWord("hhhh").char_positions.at(0), std::out_of_range);
}

TEST_CASE("vector_wrong","[vector_wrong]") {
    std::vector<std::vector<char>> puzzle{{'o', 'e', 'l', 'l', 'o'},
                                          {'l', 'a', 'l', 'e', 'o'},
                                          {'l', 'a', 'l', 'o', 'm'},
                                          {'e', 'l', 't', 'e', 'u'},
                                          {'h', 'a', 'l', 'h', 'u'}};
    WordSearchSolver wss(puzzle);
    REQUIRE_FALSE(wss.FindWord("mu").word.empty());
    REQUIRE_FALSE(wss.FindWord("mu",CheckDirection::kVertical).word.empty());
    REQUIRE(std::cout << wss.FindWord("mu").char_positions.at(0));
}
/////////////////////////////////////////////////////////////////////////////////////////////