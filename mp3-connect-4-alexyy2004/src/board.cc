#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    for (int j = 0; j < Board::kBoardWidth; ++j) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= Board::kBoardWidth || col < 0 || b.board[Board::kBoardHeight - 1][col] != DiskType::kEmpty) {
    throw std::runtime_error("adibiah");
  }
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      break;
    }
  }
}

bool CheckForWinner(Board& b, DiskType disk) {
  bool x = SearchForWinner(b, disk, WinningDirection::kHorizontal);
  bool y = SearchForWinner(b, disk, WinningDirection::kLeftDiag);
  bool z = SearchForWinner(b, disk, WinningDirection::kRightDiag);
  bool w = SearchForWinner(b, disk, WinningDirection::kVertical);
  if (x) {
    return true;
  }
  if (y) {
    return true;
  } 
  if (z) {
    return true;
  } 
  if (w) {
    return true;
  } 
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    return CheckH(b, disk);
  } 
  if (to_check == WinningDirection::kVertical) {
    return CheckV(b, disk);
  } 
  if (to_check == WinningDirection::kLeftDiag) {
    return CheckLd(b, disk);
  } 
  if (to_check == WinningDirection::kRightDiag) {
    return CheckRd(b, disk);
  }
  return false;
}

bool CheckH(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; ++i) {
      int count = 0;
      bool flag = false;
      for (int j = 0; j < Board::kBoardWidth; ++j) {
        if (flag) {
          if (b.board[i][j] == disk) {
            count += 1;
          } else {
            flag = false;
            if (count >= 4) {
              return true;
            }
            count = 0;
          }
        } else {
          if (b.board[i][j] == disk) {
            flag = true;
            count += 1;
          }
        }
      }
      if (count >= 4) {
        return true;
      }
  }
  return false;
}

bool CheckV(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; ++i) {
      int count = 0;
      bool flag = false;
      for (int j = 0; j < Board::kBoardHeight; ++j) {
        if (flag) {
          if (b.board[j][i] == disk) {
            count += 1;
          } else {
            flag = false;
            if (count >= 4) {
              return true;
            }
            count = 0;
          }
        } else {
          if (b.board[j][i] == disk) {
            flag = true;
            count += 1;
          }
        }
      }
      if (count >= 4) {
        return true;
      }
  }
  return false;
}

bool CheckLd(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; ++i) {
      for (int j = 0; j < Board::kBoardWidth; ++j) {
        if (b.board[i][j] == disk) {
          int count = 0;
          int x = i;
          int y = j;
          while (x < Board::kBoardHeight && y >= 0) {
            if (b.board[x][y] == disk) {
              count += 1;
              x += 1;
              y -= 1;
            } else {
              break;
            }
          }
          if (count >= 4) {
            return true;
          }
        }
      }
  }
  return false;
}

bool CheckRd(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; ++i) {
      for (int j = 0; j < Board::kBoardWidth; ++j) {
        if (b.board[i][j] == disk) {
          int count = 0;
          int x = i;
          int y = j;
          while (x < Board::kBoardHeight && y < Board::kBoardWidth) {
            if (b.board[x][y] == disk) {
              count += 1;
              x++;
              y++;
            } else {
              break;
            }
          }
          if (count >= 4) {
            return true;
          }
        }
      }
  }
  return false;
}
bool BoardLocationInBounds(int row, int col) {
  if (row >= 0) {
    if (row < Board::kBoardHeight) {
      if (col >= 0) {
        if (col < Board::kBoardWidth) {
          return true;
        }
      }
    }
  }
  return false;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}