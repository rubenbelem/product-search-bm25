//
// Created by rubelem on 10/30/19.
//

#include "InvertedIndex.h"

using namespace std;

bool InvertedIndex::hasWord(const string& word) {
    return this->index.find(word) != this->index.end();
}

void InvertedIndex::add(const string& word, int productIndexId) {
    ++this->index[word][productIndexId]; // update inverted list
}

int InvertedIndex::getFrequencyInProduct(const string& word, int productIndexId) {
    if (hasWord(word)) {
        if (this->index[word].find(productIndexId) != this->index[word].end()) {
            return this->index[word][productIndexId];
        }
    }

    return 0;
}

int InvertedIndex::getFrequencyInIndex(const string& word) {
    if (hasWord(word)) {
        return this->index[word].size();
    }

    return 0;
}

std::unordered_map<int, int> *InvertedIndex::getInvertedList(const std::string &word) {
    if (hasWord(word)) {
        return &this->index[word];
    }

    return nullptr;
}
