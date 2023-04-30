#include "elevation_dataset.hpp"
#include <iostream>
#include <fstream>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) {
    std::ifstream ifs(filename);
    std::vector<std::vector<int>> vec(height, std::vector<int>(width));
    for (int i = 0; i < (int)height; ++i) {
        for (int j = 0; j < (int)width; ++j) {
            int value = 0;
            ifs >> value;
            if (ifs.fail()) {
                throw std::runtime_error("read fail");
            }
            vec.at(i).at(j) = value;
        }
    }
    if (ifs.good()) {
        int value = 0;
        ifs >> value;
        if (!ifs.fail()) {
            throw std::runtime_error("too much elements");
        }
    }
    data_ = vec;
    width_ = width;
    height_ = height;
    int max = vec.at(0).at(0);
    int min = vec.at(0).at(0);
    for (int i = 0; i < (int)height; ++i) {
        for (int j = 0; j < (int)width; ++j) {
            if (data_.at(i).at(j) < min) {
                min = data_.at(i).at(j);
            }
            if (data_.at(i).at(j) > max) {
                max = data_.at(i).at(j);
            }
        }
    }
    max_ele_ = max;
    min_ele_ = min;
}

size_t ElevationDataset::Height() const {
    return height_;
}

size_t ElevationDataset::Width() const {
    return width_;
}

int ElevationDataset::MaxEle() const {
    return max_ele_;
}

int ElevationDataset::MinEle() const {
    return min_ele_;
}

int ElevationDataset::DatumAt(size_t row, size_t col) const {
    return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
    const std::vector<std::vector<int>>& temp{data_};
    return temp;
}