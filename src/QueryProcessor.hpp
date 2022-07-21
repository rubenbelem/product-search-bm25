//
// Created by rubelem on 10/30/19.
//

#ifndef BM25_SEARCH_QUERY_PROCESSOR_HPP
#define BM25_SEARCH_QUERY_PROCESSOR_HPP

#include <unordered_map>
#include "Product.hpp"
#include "InvertedIndex.hpp"
#include "ProductLengthTable.hpp"
#include "Tokenizer.hpp"
#include "QueryResult.hpp"
#include "SpellingCorrector.hpp"

class QueryProcessor {
private:
    int K;
public:
    std::string maxLengthToken;
    int correctionThreshold;

    QueryProcessor(int _K, int correctionThreshold, Tokenizer *pTokenizer);

    void indexProduct(Product product);

    std::vector<QueryResult> process(const std::string &query);

private:
    std::unordered_map<int, Product> productTable;
    InvertedIndex invertedIndex;
    ProductLengthTable productLengthTable;
    Tokenizer *tokenizer{};
    SpellingCorrector spellingCorrector;
};

#endif //BM25_SEARCH_QUERY_PROCESSOR_HPP
