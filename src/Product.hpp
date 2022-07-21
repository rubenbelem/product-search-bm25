#ifndef BM25_SEARCH_PRODUCT_HPP
#define BM25_SEARCH_PRODUCT_HPP

#include <string>

struct Product {
    std::string id;
    std::string name;
    int indexId;

    void buildFrom(const std::string &basicString);
};

#endif //BM25_SEARCH_PRODUCT_HPP
