//
// Created by rubelem on 10/30/19.
//

#ifndef BM25_SEARCH_INVERTED_INDEX_HPP
#define BM25_SEARCH_INVERTED_INDEX_HPP


#include <string>
#include <unordered_map>

class InvertedIndex {
public:
    void add(const std::string &token, int productIndexId);

    int getFrequencyInProduct(const std::string &word, int indexId);

    int getFrequencyInIndex(const std::string &word);

    bool hasWord(const std::string &token);

    std::unordered_map<int, int> *getInvertedList(const std::string &word);

private:
    std::unordered_map<std::string, std::unordered_map<int, int>> index; // maps token string to a map that represents inverted list.
};


#endif //BM25_SEARCH_INVERTED_INDEX_HPP
