#ifndef TECHNICAL_TEST_LINX_PRODUCT_HPP
#define TECHNICAL_TEST_LINX_PRODUCT_HPP

#include <string>

struct Product {
    std::string id;
    std::string name;
    int indexId;

    void buildFrom(const std::string &basicString);
};

#endif //TECHNICAL_TEST_LINX_PRODUCT_HPP
