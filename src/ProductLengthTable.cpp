//
// Created by rubelem on 10/30/19.
//

#include "ProductLengthTable.h"

void ProductLengthTable::add(int productIndexId, int length) {
    this->table[productIndexId] = length;
}

bool ProductLengthTable::tableHasId(int id) {
    return this->table.find(id) != this->table.end();
}

int ProductLengthTable::getLength(int productIndexId) {
    if (tableHasId(productIndexId)) {
        return this->table[productIndexId];
    }

    return 0;
}

int ProductLengthTable::getTableSize() {
    return this->table.size();
}

double ProductLengthTable::getAverageSize() {
    double sum = 0.0;

    for (auto tableItem : this->table) {
        double length = (double) tableItem.second;
        sum += length;
    }

    return sum / (double) this->table.size();
}