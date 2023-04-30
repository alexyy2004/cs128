#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
#include <iostream>
#include <cmath>
int main() {
    const std::string& str{"/home/vagrant/src/mp5-mountain-paths-alexyy2004/example-data/ex_input_data/data.dat"};
    size_t width = 5;
    size_t height = 3;
    ElevationDataset e(str, width, height);
    const ElevationDataset& temp{e};
    GrayscaleImage g{temp};
    //std::cout << g.GetImage().at(0).at(0).Blue() << std::endl;
    //std::cout << round((double)(1)/(double)(3)*255) << std::endl;
    //g.ToPpm("/home/vagrant/src/mp5-mountain-paths-alexyy2004/aaa.ppm");
    PathImage p(g, e);
    p.ToPpm("bbb.ppm");
    for (int i = 0; i < (int)p.Paths().size(); ++i) {
        std::cout << p.Paths().at(i).EleChange() << std::endl;
    }
}