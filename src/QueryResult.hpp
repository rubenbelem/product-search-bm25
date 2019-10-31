//
// Created by rubelem on 10/30/19.
//

#ifndef TECHNICAL_TEST_LINX_QUERYRESULT_HPP
#define TECHNICAL_TEST_LINX_QUERYRESULT_HPP

#include "Product.hpp"

struct QueryResult {
    Product product{};
    double score;

    QueryResult(const Product &product, double score);
};


#endif //TECHNICAL_TEST_LINX_QUERYRESULT_HPP
