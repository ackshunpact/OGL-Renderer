//
// Created by bigbeev on 8/1/2025.
//

#ifndef IMAGEREGISTRY_H
#define IMAGEREGISTRY_H
#include <string>

#include "Image.h"
#include "Registry.h"


class ImageRegistry : public Registry<Image> {
public:
    ImageRegistry() {}
    std::shared_ptr<Image> get(const std::string &name) {
        return assets[name];
    }

    void insert(const std::string &name, const std::string& path);

    std::shared_ptr<Image> loadAsset(const std::string& name);

private:
    void test();
};



#endif //IMAGEREGISTRY_H
