//
// Created by rubelem on 10/30/19.
//

#ifndef TECHNICAL_TEST_LINX_QUERYRESULT_H
#define TECHNICAL_TEST_LINX_QUERYRESULT_H

#include "Product.h"

struct QueryResult {
    Product product{};
    double score;

    QueryResult(const Product &product, double score);
};


#endif //TECHNICAL_TEST_LINX_QUERYRESULT_H
