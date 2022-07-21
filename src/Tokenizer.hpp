//
// Created by rubelem on 10/29/19.
//

#ifndef BM25_SEARCH_TOKENIZER_HPP
#define BM25_SEARCH_TOKENIZER_HPP

#include <string>
#include <vector>
#include <unordered_map>

class Tokenizer {
public:
    std::vector<std::string> extractFrom(const std::string &s);

    Tokenizer();

    // Tokenizer can take a stop words file in a constructor parameter, to read it and build stopWordsMap.
    explicit Tokenizer(std::ifstream &stopWordsFile);

private:
    std::unordered_map<std::string, bool> stopWordsMap; // the unoderderd_map allows fast lookup to check whether a string is a stop word.
    bool isStopWord(const std::string &s);
};

#endif //BM25_SEARCH_TOKENIZER_HPP
