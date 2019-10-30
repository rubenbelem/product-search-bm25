#ifndef TECHNICAL_TEST_LINX_PRODUCT_H
#define TECHNICAL_TEST_LINX_PRODUCT_H

#include <string>

struct Product {
    std::string id;
    std::string name;
    int indexId;

    void buildFrom(const std::string &basicString);
};

#endif //TECHNICAL_TEST_LINX_PRODUCT_H
