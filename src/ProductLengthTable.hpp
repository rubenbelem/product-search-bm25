//
// Created by rubelem on 10/30/19.
//

#ifndef BM25_SEARCH_PRODUCT_LENGTH_TABLE_HPP
#define BM25_SEARCH_PRODUCT_LENGTH_TABLE_HPP

#include <unordered_map>

class ProductLengthTable {

public:
    void add(int productIndexId, int length);

    int getLength(int productIndexId);

    int getTableSize();

    double getAverageSize();

    bool tableHasId(int id);

private:
    std::unordered_map<int, int> table;
};


#endif //BM25_SEARCH_PRODUCT_LENGTH_TABLE_HPP
