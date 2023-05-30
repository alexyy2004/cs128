#include "seam_carver.hpp"
#include <iostream>

// implement the rest of SeamCarver's functions here
const ImagePPM& SeamCarver::GetImage() const {
  const ImagePPM& temp = image_;
  return temp;
}

int SeamCarver::GetHeight() const {
  return height_;
}

int SeamCarver::GetWidth() const {
  return width_;
}

int SeamCarver::GetEnergy(int row, int col) const {
  int num = 0;
  Pixel up = image_.GetPixel((row - 1 + height_) % height_, col);
  Pixel down = image_.GetPixel((row + 1 + height_) % height_, col);
  Pixel left = image_.GetPixel(row, (col - 1 + width_) % width_);
  Pixel right = image_.GetPixel(row, (col + 1 + width_) % width_);
  num = (up.GetBlue() - down.GetBlue()) * (up.GetBlue() - down.GetBlue())
          + (up.GetGreen() - down.GetGreen()) * (up.GetGreen() - down.GetGreen())
          + (up.GetRed() - down.GetRed()) * (up.GetRed() - down.GetRed())
          + (left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue())
          + (left.GetGreen() - right.GetGreen()) * (left.GetGreen() - right.GetGreen())
          + (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed());
  return num;
}

int* SeamCarver::GetHorizontalSeam() const{
  int** verticalvalue = new int*[height_];
  for (int i = 0; i < height_; ++i) {
    verticalvalue[i] = new int[width_];
  }
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      verticalvalue[i][j] = GetEnergy(i, j);
    }
  }
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      if (row == 0) {
        verticalvalue[row][col] += std::min(verticalvalue[row][col + 1], verticalvalue[row + 1][col + 1]);
      } else if (row == height_ - 1) {
        verticalvalue[row][col] += std::min(verticalvalue[row][col + 1], verticalvalue[row - 1][col + 1]);
      } else {
        int temp = std::min(verticalvalue[row - 1][col + 1], verticalvalue[row][col + 1]);
        verticalvalue[row][col] += std::min(temp, verticalvalue[row + 1][col + 1]);
      }
    } 
  }
  int* result = new int[width_];
  int min = verticalvalue[0][0];
  int minindex = 0;
  for (int row = 1; row < height_; row++) {
    if (verticalvalue[row][0] < min) {
      min = verticalvalue[row][0];minindex = row;
    }
  }
  result[0] = minindex;
  for (int col = 1; col < width_; col++) {
    int index = 0;
    if (result[col - 1] == 0) {
      if (verticalvalue[0][col] <= verticalvalue[1][col]) {
        index = 0;
      } else {
        index = 1;
      }
    } else if (result[col - 1] == height_ - 1) {
      if (verticalvalue[result[col - 1] - 1][col] >= verticalvalue[result[col - 1]][col]) {
        index = result[col - 1];
      } else {
        index = result[col - 1] - 1;
      }
    } else {
      int row = result[col - 1];
      if (verticalvalue[row - 1][col] == verticalvalue[row][col] && verticalvalue[row][col] == verticalvalue[row + 1][col]) {
        index = row;
      } else {
        int temp = std::min(verticalvalue[row - 1][col], verticalvalue[row][col]);
        int min = std::min(temp, verticalvalue[row + 1][col]);
        if (min == verticalvalue[row][col]) {
          index = row;
        } else if (min == verticalvalue[row - 1][col]) {
          index = row - 1;
        } else {
          index = row + 1;
        }
      }
    }
    result[col] = index;
  }
  for (int i = 0; i < height_; i++) {
    delete[] verticalvalue[i];
  }
  delete[] verticalvalue;
  return result;
}

int* SeamCarver::GetVerticalSeam() const {
  int** horizontalvalue = new int*[height_];
  for (int i = 0; i < height_; ++i) {
    horizontalvalue[i] = new int[width_];
  }
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      horizontalvalue[i][j] = GetEnergy(i, j);
    }
  }
  for (int i = height_ - 2; i >= 0; i--) {
    for (int j = 0; j < width_; j++) {
      if (j == 0) {
        horizontalvalue[i][j] += std::min(horizontalvalue[i + 1][j], horizontalvalue[i + 1][j + 1]);
      } else if (j == width_ - 1) {
        horizontalvalue[i][j] += std::min(horizontalvalue[i + 1][j - 1], horizontalvalue[i + 1][j]);
      } else {
        int temp = std::min(horizontalvalue[i + 1][j - 1], horizontalvalue[i + 1][j]);
        horizontalvalue[i][j] += std::min(temp, horizontalvalue[i + 1][j + 1]);
      }
    }
  }
  int* result = new int[height_];
  int min = horizontalvalue[0][0];
  int minindex = 0;
  for (int i = 0; i < width_; i++) {
    if (horizontalvalue[0][i] < min) {
      min = horizontalvalue[0][i];
      minindex = i;
    }
  }
  result[0] = minindex;
  for (int row = 1; row < height_; row++) {
    int index = 0;
    if (result[row - 1] == 0) {
      if (horizontalvalue[row][0] <= horizontalvalue[row][1]) {
        index = 0;
      } else {
        index = 1;
      }
    } else if (result[row - 1] == width_ - 1) {
      int col = result[row - 1];
      if (horizontalvalue[row][col - 1] >= horizontalvalue[row][col]) {
        index = col;
      } else {
        index = col - 1;
      }
    } else {
      int col = result[row - 1];
      if (horizontalvalue[row][col - 1] == horizontalvalue[row][col] && horizontalvalue[row][col] == horizontalvalue[row][col + 1]) {
        index = col;
      } else {
        int temp = std::min(horizontalvalue[row][col - 1], horizontalvalue[row][col]);
        int min = std::min(temp, horizontalvalue[row][col + 1]);
        if (min == horizontalvalue[row][col]) {
          index = col;
        } else if (min == horizontalvalue[row][col - 1]) {
          index = col - 1;
        } else {
          index = col + 1;
        }
      }
    }
    result[row] = index;
  }
  for (int i = 0; i < height_; i++) {
    delete[] horizontalvalue[i];
  }
  delete[] horizontalvalue;
  return result;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* seam = GetHorizontalSeam();
  height_ -= 1;
  Pixel** pixels = new Pixel*[height_];
  for (int i = 0; i < height_; i++) {
    pixels[i] = new Pixel[width_];
  }
  ImagePPM result(width_, height_, image_.GetMaxColorValue(), pixels);
  //result.SetHeight();
  for (int col = 0; col < width_; col++) {
    bool flag = false;
    for (int row = 0; row < result.GetHeight(); row++) {
      if (row == seam[col] || flag) {
        result.GetPixels()[row][col] = image_.GetPixels()[row + 1][col];
        flag = true;
      } else {
        result.GetPixels()[row][col] = image_.GetPixels()[row][col];
      }
    }
  }
  delete[] seam;
  //seam = nullptr;
  image_.~ImagePPM();
  SetImage(result);
  //seam = nullptr;
  //image_.~ImagePPM();
  //image_ = result;
  //height_ -= result.GetHeight(); 
  //SetImage(result);
  //result.~ImagePPM();
}

void SeamCarver::RemoveVerticalSeam() {
  int* seam = GetVerticalSeam();
  ImagePPM result = image_;
  //result.~ImagePPM();
  result.SetWidth();
  for (int row = 0; row < height_; row++) {
    bool flag = false;
    for (int col = 0; col < result.GetWidth(); col++) {
      if (col == seam[row] || flag) {
        result.GetPixels()[row][col] = image_.GetPixels()[row][col + 1];
        flag = true;
      } else {
        result.GetPixels()[row][col] = image_.GetPixels()[row][col];
      }
    }
  }
  delete[] seam;
  //seam = nullptr;
  image_.~ImagePPM();
  SetImage(result);
  //result.~ImagePPM();
  //result.~ImagePPM();
  //seam = nullptr;
  //SetImage(result);
  //image_ = result;
  //width_ -= 1;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
