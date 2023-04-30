#include "WordSearchSolver.hpp"
#include <stdexcept>
#include <iostream>
bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(const std::vector<std::vector<char>>& puzzle) {
  puzzle_ = puzzle;
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle.at(0).size();
}

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {
  if (LocationInBounds(puzzle_.size(),puzzle_.at(0).size())) {
    throw std::invalid_argument("aaa");
  }
  if (direction == CheckDirection::kHorizontal) {
    return FindHorizontalWord(word);
  }
  if (direction == CheckDirection::kVertical) {
    return FindVerticalWord(word);
  }
  if (direction == CheckDirection::kLeftDiag) {
    return FindLeftDiagWord(word);
  } 
  if (direction == CheckDirection::kRightDiag) {
    return FindRightDiagWord(word);
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  if (LocationInBounds(puzzle_.size(),puzzle_.at(0).size())) {
    throw std::invalid_argument("aaa");
  }
  if (FindWord(word, CheckDirection::kHorizontal).word.empty()) {
    if (FindWord(word, CheckDirection::kVertical).word.empty()) {
      if (FindWord(word, CheckDirection::kLeftDiag).word.empty()) {
        if (FindWord(word, CheckDirection::kRightDiag).word.empty()) {
          return WordLocation{};
        } else {
          return FindWord(word, CheckDirection::kRightDiag);
        }
      } else {
        return FindWord(word, CheckDirection::kLeftDiag);
      }
    } else {
      return FindWord(word, CheckDirection::kVertical);
    }
  } else {
    return FindWord(word, CheckDirection::kHorizontal);
  }
}

WordLocation WordSearchSolver::FindHorizontalWord(const std::string& word) {
  if (LocationInBounds(puzzle_.size(),puzzle_.at(0).size())) {
    throw std::invalid_argument("aaa");
  }
  for (int i = 0; i < (int)puzzle_.size(); ++i) {
    for (int j = 0; j <= (int)(puzzle_.at(i).size() - word.size()); ++j) {
      std::string temp;
      std::vector<CharPositions> cps;
      for (int k = j; k < int(j + word.size()); ++k) {
        temp += puzzle_.at(i).at(k);
        CharPositions cp = {puzzle_.at(i).at(k),(unsigned int)i,(unsigned int)k};
        cps.push_back(cp);
      }
      if (temp == word) {
        return WordLocation{word, cps};
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindVerticalWord(const std::string& word) {
  if (LocationInBounds(puzzle_.size(),puzzle_.at(0).size())) {
    throw std::invalid_argument("aaa");
  }
  for (int i = 0; i < (int)puzzle_.at(0).size(); ++i) {
    for (int j = 0; j <= (int)(puzzle_.size() - word.size()); ++j) {
      std::string temp;
      std::vector<CharPositions> cps;
      for (int k = j; k < (int)(j + word.size()); ++k) {
        temp += puzzle_.at(k).at(i);
        CharPositions cp = {puzzle_.at(k).at(i),(unsigned int)k,(unsigned int)i};
        cps.push_back(cp);
      }
      if (temp == word) {
        return WordLocation{word, cps};
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindLeftDiagWord(const std::string& word) {
  if (LocationInBounds(puzzle_.size(),puzzle_.at(0).size())) {
    throw std::invalid_argument("aaa");
  }
  for (int i = 0; i < (int)puzzle_.size(); ++i) {
    for (int j = 0; j < (int)puzzle_.at(i).size(); ++j) {
      std::string temp;
      int x = i;
      int y = j;
      while (x < (int)puzzle_.size() && y >= 0) {
        temp += puzzle_.at(x).at(y);
        x++;
        y--;
      }
      if (temp.find(word) != std::string::npos) {
        unsigned int pos = temp.find(word);
        std::vector<CharPositions> cps;
        for (int m = 0; m < (int)word.size(); ++m) {
          CharPositions cp = {puzzle_.at(i + pos + m).at(j - pos - m), (unsigned int)(i + pos + m), (unsigned int)(j - pos - m)};
          cps.push_back(cp);
        }
        return WordLocation{word, cps};
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindRightDiagWord(const std::string& word) {
  if (LocationInBounds(puzzle_.size(),puzzle_.at(0).size())) {
    throw std::invalid_argument("aaa");
  }
  for (int i = 0; i < (int)puzzle_.size(); ++i) {
    for (int j = 0; j < (int)puzzle_.at(i).size(); ++j) {
      std::string temp;
      int x = i;
      int y = j;
      while (x < (int)puzzle_.size() && y < (int)puzzle_.at(0).size()) {
        temp += puzzle_.at(x).at(y);
        x++;
        y++;
      }
      if (temp.find(word) != std::string::npos) {
        unsigned int pos = temp.find(word);
        std::vector<CharPositions> cps;
        for (int m = 0; m < (int)word.size(); ++m) {
          CharPositions cp = {puzzle_.at(i + pos + m).at(j + pos + m), (unsigned int)(i + pos + m), (unsigned int)(j + pos + m)};
          cps.push_back(cp);
        }
        return WordLocation{word, cps};
      }
    }
  }
  return WordLocation{};
}