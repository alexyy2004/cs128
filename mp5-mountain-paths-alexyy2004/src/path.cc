#include "path.hpp"
#include "elevation_dataset.hpp"

Path::Path(size_t length, size_t starting_row) {
    std::vector<size_t> path(length);
    length_ = length;
    starting_row_ = starting_row;
    path_ = path;
}

size_t Path::Length() const {
    return length_;
}

size_t Path::StartingRow() const {
    return starting_row_;
}

unsigned int Path::EleChange() const {
    return ele_change_;
}

void Path::IncEleChange(unsigned int value) {
    ele_change_ += value;
}

const std::vector<size_t>& Path::GetPath() const {
    const std::vector<size_t>& temp {path_};
    return temp;
}

void Path::SetLoc(size_t col, size_t row) {
    path_.at(col) = row;
}