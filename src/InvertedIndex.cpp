//
// Created by rubelem on 10/30/19.
//

#include "InvertedIndex.h"

using namespace std;

bool InvertedIndex::indexHasWord(string word) {
    return this->index.find(word) != this->index.end();
}

void InvertedIndex::add(std::string word, int productIndexId) {
    ++this->index[word][productIndexId]; // update inverted list
}

int InvertedIndex::getFrequencyInProduct(std::string word, int productIndexId) {
    if (indexHasWord(word)) {
        if (this->index[word].find(productIndexId) != this->index[word].end()) {
            return this->index[word][productIndexId];
        }
    }

    return 0;
}

int InvertedIndex::getFrequencyInIndex(std::string word) {
    if (indexHasWord(word)) {
        return this->index[word].size();
    }

    return 0;
}
