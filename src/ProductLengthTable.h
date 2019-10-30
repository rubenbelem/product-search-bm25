//
// Created by rubelem on 10/30/19.
//

#ifndef TECHNICAL_TEST_LINX_PRODUCTLENGTHTABLE_H
#define TECHNICAL_TEST_LINX_PRODUCTLENGTHTABLE_H

#include <unordered_map>

class ProductLengthTable {

public:
    void add(int productIndexId, int length);
    int getLength(int productIndexId);
    int getTableSize();
private:
    std::unordered_map<int, int> table;

    bool tableHasId(int id);
};


#endif //TECHNICAL_TEST_LINX_PRODUCTLENGTHTABLE_H
