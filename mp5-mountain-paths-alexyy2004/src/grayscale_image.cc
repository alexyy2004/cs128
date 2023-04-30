#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"
#include <cmath>
#include <fstream>

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    const int kValue = 255;
    std::vector<std::vector<int>> data = dataset.GetData();
    std::vector<std::vector<Color>> color(dataset.Height(), std::vector<Color>(dataset.Width()));
    for (int i = 0; i < (int)data.size(); ++i) {
        for (int j = 0; j < (int)data.at(i).size(); ++j) {
            int elevation_point = data.at(i).at(j);
            int min_ele = dataset.MinEle();
            int max_ele = dataset.MaxEle();
            int shade_of_gray = 0;
            if (min_ele == max_ele) {
                shade_of_gray = 0;
            } else {
                shade_of_gray = std::round((double)(elevation_point - min_ele) / (double)(max_ele - min_ele) * kValue);
            }
            Color c(shade_of_gray, shade_of_gray, shade_of_gray);
            color.at(i).at(j) = c;
        }
    }
    image_ = color;
    width_ = dataset.Width();
    height_ = dataset.Height();
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
    const int kValue = 255;
    ElevationDataset dataset = ElevationDataset(filename, width, height);
    std::vector<std::vector<int>> data = dataset.GetData();
    std::vector<std::vector<Color>> color(dataset.Height(), std::vector<Color>(dataset.Width()));
    for (int i = 0; i < (int)data.size(); ++i) {
        for (int j = 0; j < (int)data.at(i).size(); ++j) {
            int elevation_point = data.at(i).at(j);
            int min_ele = dataset.MinEle();
            int max_ele = dataset.MaxEle();
            int shade_of_gray = 0;
            if (min_ele == max_ele) {
                shade_of_gray = 0;
            } else {
                shade_of_gray = std::round((double)(elevation_point - min_ele) / (double)(max_ele - min_ele) * kValue);
            }
            Color c(shade_of_gray, shade_of_gray,shade_of_gray);
            color.at(i).at(j) = c;
        }
    }
    image_ = color;
    width_ = dataset.Width();
    height_ = dataset.Height();
}

size_t GrayscaleImage::Width() const {
    return width_;
}

size_t GrayscaleImage::Height() const {
    return height_;
}

unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
    const Color& temp{image_.at(row).at(col)};
    return temp;
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
    const std::vector<std::vector<Color>>& temp {image_};
    return temp;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
    std::ofstream fout(name);
    if (fout.fail()) {
        throw std::runtime_error("bkabjbkd");
    }
    fout << "P3\n";
    fout << width_ << " " << height_ << "\n";
    fout << "255\n";
    for (int i = 0; i < (int)height_; ++i) {
        for (int j = 0; j < (int)width_; ++j) {
            fout << image_.at(i).at(j).Red() << " ";
            fout << image_.at(i).at(j).Green() << " ";
            fout << image_.at(i).at(j).Blue() << " ";
        }
        fout << "\n";
    }
    fout << "\n";
    fout.close();
}