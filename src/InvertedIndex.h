//
// Created by rubelem on 10/30/19.
//

#ifndef TECHNICAL_TEST_LINX_INVERTEDINDEX_H
#define TECHNICAL_TEST_LINX_INVERTEDINDEX_H


#include <string>
#include <unordered_map>
#include <boost/locale/utf8_codecvt.hpp>
#include <nuspell/dictionary.hxx>
#include <nuspell/finder.hxx>

class InvertedIndex {
public:
    nuspell::Dictionary dict;
    void add(const std::string &token, int productIndexId);

    int getFrequencyInProduct(const std::string &word, int indexId);

    int getFrequencyInIndex(const std::string &word);

    bool hasWord(const std::string &token);

    std::unordered_map<int, int> *getInvertedList(const std::string &word);

private:
    std::unordered_map<std::string, std::unordered_map<int, int>> index; // maps token string to a map that represents inverted list.
};


#endif //TECHNICAL_TEST_LINX_INVERTEDINDEX_H
