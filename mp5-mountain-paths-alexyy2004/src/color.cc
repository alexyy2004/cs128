#include "color.hpp"
#include <iostream>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  const int kValue = 255;
  if (r < 0 || r > kValue || g < 0 || g > kValue || b < 0 || b > kValue) {
    throw std::invalid_argument("invalid RGB");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}