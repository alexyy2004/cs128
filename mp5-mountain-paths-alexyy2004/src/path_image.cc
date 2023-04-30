#include "path_image.hpp"
#include <fstream>

PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) {
    path_image_ = image.GetImage();width_ = dataset.Width();height_ = dataset.Height();std::vector<Path> paths;
    for (int i = 0; i < (int)dataset.Height(); ++i) {
        int start_row = i;Path p {(size_t)(dataset.Width()), (size_t)(start_row)};p.SetLoc((size_t)(0), (size_t)(start_row));
        int current_column = 0;int current_row = start_row;
        while (current_column < (int)(dataset.Width()) - 1) {
            if (current_row == 0) {
                int right = abs(dataset.DatumAt(current_row, current_column) - dataset.DatumAt(current_row, current_column + 1));
                int down_right = abs(dataset.DatumAt(current_row, current_column) - dataset.DatumAt(current_row + 1, current_column + 1));
                int value = 0;current_column += 1;
                if (right <= down_right) {value = right;} else {value = down_right;current_row += 1;}
                p.IncEleChange(value);p.SetLoc((size_t)(current_column), (size_t)(current_row));
            } else if (current_row == (int)(dataset.Height()) - 1) {
                int right = abs(dataset.DatumAt((size_t)current_row, (size_t)current_column) - dataset.DatumAt((size_t)current_row, (size_t)current_column + 1));
                int up_right = abs(dataset.DatumAt((size_t)current_row, (size_t)current_column) - dataset.DatumAt((size_t)current_row - 1, (size_t)current_column + 1));
                int value = 0;current_column += 1;
                if (right <= up_right) {value = right;} else {value = up_right;current_row -= 1;}
                p.IncEleChange(value);p.SetLoc((size_t)current_column, (size_t)current_row);
            } else {
                int up_right = abs(dataset.DatumAt(current_row, current_column) - dataset.DatumAt(current_row - 1, current_column + 1));
                int right = abs(dataset.DatumAt(current_row, current_column) - dataset.DatumAt(current_row, current_column + 1));
                int down_right = abs(dataset.DatumAt(current_row, current_column) - dataset.DatumAt(current_row + 1, current_column + 1));
                int result = 0;current_column += 1;
                if (right <= up_right && right <= down_right) {result = right;} else if (down_right <= right && down_right <= up_right) {result = down_right;current_row += 1;} else {result = up_right;current_row -= 1;}
                p.IncEleChange(result);p.SetLoc((size_t)current_column, (size_t)current_row);
            }
        }
        paths.push_back(p);
    }
    paths_ = paths;
    const int kValueR = 252;const int kValueG = 25;const int kValueB = 63;
    const int kGreenValueR = 31;const int kGreenValueG = 253;const int kGreenValueB = 13;
    for (Path p : paths_) {for (int i = 0; i < (int)p.GetPath().size(); ++i) {path_image_.at(p.GetPath().at(i)).at(i) = Color(kValueR, kValueG, kValueB);}}
    int best_path_row = 0;unsigned int min_ele = paths_.at(0).EleChange();
    for (int i = 0; i < (int)paths_.size(); ++i) {if (paths_.at(i).EleChange() < min_ele) {min_ele = paths_.at(i).EleChange();}}
    for (int i = 0; i < (int)paths_.size(); ++i) {if (paths_.at(i).EleChange() == min_ele) {best_path_row = (int)(paths_.at(i).StartingRow());break;}}
    for (int i = 0; i < (int)paths_.size(); ++i) {if ((int)paths_.at(i).StartingRow() == best_path_row) {for (int j = 0; j < (int)paths_.at(i).GetPath().size(); ++j) {path_image_.at(paths_.at(i).GetPath().at(j)).at(j) = Color(kGreenValueR, kGreenValueG, kGreenValueB);}break;}}}

size_t PathImage::Width() const {
    return width_;
}

size_t PathImage::Height() const {
    return height_;
}

unsigned int PathImage::MaxColorValue() const {
    return kMaxColorValue;
}

const std::vector<Path>& PathImage::Paths() const {
    const std::vector<Path>& temp{paths_};
    return temp;
}

const std::vector<std::vector<Color> >& PathImage::GetPathImage() const {
    const std::vector<std::vector<Color> >& temp{path_image_};
    return temp;
}

void PathImage::ToPpm(const std::string& name) const {
    std::ofstream fout(name);
    if (fout.fail()) {
        throw std::runtime_error("bkabjbkd");
    }
    fout << "P3\n";
    fout << width_ << " " << height_ << "\n";
    fout << "255\n";
    for (int i = 0; i < (int)height_; ++i) {
        for (int j = 0; j < (int)width_; ++j) {
            fout << path_image_.at(i).at(j).Red() << " ";
            fout << path_image_.at(i).at(j).Green() << " ";
            fout << path_image_.at(i).at(j).Blue() << " ";
        }
        fout << "\n";
    }
    fout << "\n";
    fout.close();
}