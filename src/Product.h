#ifndef TECHNICAL_TEST_LINX_PRODUCT_H
#define TECHNICAL_TEST_LINX_PRODUCT_H

struct Product {
    std::string id;
    std:: string name;

    void buildFrom(const std::string& basicString);
};

#endif //TECHNICAL_TEST_LINX_PRODUCT_H
