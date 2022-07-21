//
// Created by rubelem on 10/30/19.
//

#ifndef BM25_SEARCH_QUERY_RESULT_HPP
#define BM25_SEARCH_QUERY_RESULT_HPP

#include "Product.hpp"

struct QueryResult {
    Product product{};
    double score;

    QueryResult(const Product &product, double score);
};


#endif //BM25_SEARCH_QUERY_RESULT_HPP
