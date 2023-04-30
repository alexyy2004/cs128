// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
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

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Check vertical", "[vertical]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  REQUIRE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE(CheckForWinner(student,DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student,DiskType::kPlayer2));
}

TEST_CASE("Check horizontal", "[horizontal]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer1,2);
  DropDiskToBoard(student,DiskType::kPlayer1,3);
  DropDiskToBoard(student,DiskType::kPlayer1,4);
  REQUIRE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE(CheckForWinner(student,DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student,DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE_FALSE(BoardLocationInBounds(Board::kBoardHeight,Board::kBoardWidth));
  REQUIRE_FALSE(BoardLocationInBounds(-1,-1));
}

TEST_CASE("Check right_diagonal", "[right_diagonal]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student,DiskType::kPlayer1,0);
  DropDiskToBoard(student,DiskType::kPlayer2,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer1,2);
  DropDiskToBoard(student,DiskType::kPlayer2,3);
  DropDiskToBoard(student,DiskType::kPlayer2,3);
  DropDiskToBoard(student,DiskType::kPlayer2,3);
  DropDiskToBoard(student,DiskType::kPlayer1,3);
  REQUIRE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE(CheckForWinner(student,DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student,DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE_FALSE(BoardLocationInBounds(Board::kBoardHeight,Board::kBoardWidth));
  REQUIRE_FALSE(BoardLocationInBounds(-1,-1));
}

TEST_CASE("Check left_diagonal", "[left_diagonal]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer1,0);
  DropDiskToBoard(student,DiskType::kPlayer2,1);
  DropDiskToBoard(student,DiskType::kPlayer2,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer1,2);
  DropDiskToBoard(student,DiskType::kPlayer1,3);
  REQUIRE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE(CheckForWinner(student,DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student,DiskType::kPlayer2));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(BoardLocationInBounds(Board::kBoardHeight,Board::kBoardWidth));
  REQUIRE_FALSE(BoardLocationInBounds(-1,-1));
}

TEST_CASE("Check no one win", "[no_one_win]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer1,0);
  DropDiskToBoard(student,DiskType::kPlayer1,0);
  DropDiskToBoard(student,DiskType::kPlayer1,0);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer2,1);
  DropDiskToBoard(student,DiskType::kPlayer2,1);
  DropDiskToBoard(student,DiskType::kPlayer2,1);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer1,2);
  DropDiskToBoard(student,DiskType::kPlayer1,2);
  DropDiskToBoard(student,DiskType::kPlayer1,2);
  DropDiskToBoard(student,DiskType::kPlayer1,3);
  DropDiskToBoard(student,DiskType::kPlayer1,3);
  DropDiskToBoard(student,DiskType::kPlayer1,3);
  DropDiskToBoard(student,DiskType::kPlayer2,3);
  DropDiskToBoard(student,DiskType::kPlayer2,3);
  DropDiskToBoard(student,DiskType::kPlayer2,3);
  DropDiskToBoard(student,DiskType::kPlayer2,4);
  DropDiskToBoard(student,DiskType::kPlayer2,4);
  DropDiskToBoard(student,DiskType::kPlayer2,4);
  DropDiskToBoard(student,DiskType::kPlayer1,4);
  DropDiskToBoard(student,DiskType::kPlayer1,4);
  DropDiskToBoard(student,DiskType::kPlayer1,4);
  DropDiskToBoard(student,DiskType::kPlayer1,5);
  DropDiskToBoard(student,DiskType::kPlayer1,5);
  DropDiskToBoard(student,DiskType::kPlayer1,5);
  DropDiskToBoard(student,DiskType::kPlayer2,5);
  DropDiskToBoard(student,DiskType::kPlayer2,5);
  DropDiskToBoard(student,DiskType::kPlayer2,5);
  DropDiskToBoard(student,DiskType::kPlayer2,6);
  DropDiskToBoard(student,DiskType::kPlayer2,6);
  DropDiskToBoard(student,DiskType::kPlayer2,6);
  DropDiskToBoard(student,DiskType::kPlayer1,6);
  DropDiskToBoard(student,DiskType::kPlayer1,6);
  DropDiskToBoard(student,DiskType::kPlayer1,6);
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(CheckForWinner(student,DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student,DiskType::kPlayer2));
}

TEST_CASE("Check bounds", "[check_bounds]") {
  REQUIRE_FALSE(BoardLocationInBounds(Board::kBoardHeight,Board::kBoardWidth));
  REQUIRE(BoardLocationInBounds(0,0));
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight - 1, Board::kBoardWidth - 1));
}

TEST_CASE("drop out of bound", "[drop_out_of_bound]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 0),std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -19),std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 99),std::runtime_error);
}
/*
TEST_CASE("greatest diagonal", "[left_greateset_diagonal]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student,DiskType::kPlayer1,0);
  DropDiskToBoard(student,DiskType::kPlayer1,0);
  DropDiskToBoard(student,DiskType::kPlayer1,0);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer2,0);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer2,1);
  DropDiskToBoard(student,DiskType::kPlayer1,1);
  DropDiskToBoard(student,DiskType::kPlayer2,1);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer1,2);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer2,2);
  DropDiskToBoard(student,DiskType::kPlayer1,3);
  DropDiskToBoard(student,DiskType::kPlayer2,3);
  DropDiskToBoard(student,DiskType::kPlayer2,3);
  DropDiskToBoard(student,DiskType::kPlayer2,4);
  DropDiskToBoard(student,DiskType::kPlayer1,4);
  DropDiskToBoard(student,DiskType::kPlayer1,5);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student,DiskType::kPlayer1,WinningDirection::kLeftDiag));
}
*/

TEST_CASE("greatest right diagonal", "[greatest_right_diagonal]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  REQUIRE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
}
/////////////////////////////////////////////////////////////////////////////////////////////