//
// Created by rubelem on 10/30/19.
//

#ifndef TECHNICAL_TEST_LINX_INVERTEDINDEX_H
#define TECHNICAL_TEST_LINX_INVERTEDINDEX_H


#include <string>
#include <unordered_map>

class InvertedIndex {
public:
    void add(std::string token, int productIndexId);
    int getFrequencyInProduct(std::string word, int indexId);
    int getFrequencyInIndex(std::string word);
//private:

    std::unordered_map<std::string, std::unordered_map<int, int>> index; // maps token string to a map that represents inverted list.
    bool indexHasWord(std::string token);
};


#endif //TECHNICAL_TEST_LINX_INVERTEDINDEX_H
