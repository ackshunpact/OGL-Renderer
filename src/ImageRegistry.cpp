//
// Created by bigbeev on 8/1/2025.
//

#include "ImageRegistry.h"
#define STB_IMAGE_IMPLEMENTATION
#include <fstream>

#include "stb_image.h"
#include <iostream>
void ImageRegistry::insert(const std::string &name, const std::string& path) {
    std::shared_ptr<Image> image = loadAsset(path);
    assets.insert(std::make_pair(name, image));
}
std::shared_ptr<Image> ImageRegistry::loadAsset(const std::string& name) {
    std::shared_ptr<Image> image = std::make_shared<Image>();
    int width, height, nrChannels;
    unsigned char *data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
    image->width = width;
    image->height = height;
    size_t size = static_cast<size_t>(width) * height * nrChannels;

    image->data = std::vector<uint8_t>(data, data + size);
    stbi_image_free(data);

    return image;
}

void ImageRegistry::test() {

    ImageRegistry iReg = ImageRegistry();
    iReg.insert("wall1", "D:/dev/cpp/ducky/assets/wall.jpg");
    std::shared_ptr<Image> img = iReg.get("wall1");


    int image_width = img->width;
    int image_height = img->height;

    std::ofstream outfile("D:/dev/cpp/ducky/texture_test.ppm", std::ios::out);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;

    }
    // Render
    outfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height * image_width * 3; j+=3) {
        // for (int i = 0; i < image_width; i++) {
        // auto r = double(i) / (image_width-1);
        // auto g = double(j) / (image_height-1);
        // auto b = 0.0;
        //
        // int ir = int(255.999 * r);
        // int ig = int(255.999 * g);
        // int ib = int(255.999 * b);

        // outfile << img->data[j] << ' ' << img->data[j+1] << ' ' << img->data[j+2] << '\n';
        outfile << static_cast<int>(img->data[j]) << ' '
            << static_cast<int>(img->data[j + 1]) << ' '
            << static_cast<int>(img->data[j + 2]) << '\n';

    }
}
