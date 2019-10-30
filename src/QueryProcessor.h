//
// Created by rubelem on 10/30/19.
//

#ifndef TECHNICAL_TEST_LINX_QUERYPROCESSOR_H
#define TECHNICAL_TEST_LINX_QUERYPROCESSOR_H

#include <unordered_map>
#include "Product.h"
#include "InvertedIndex.h"
#include "ProductLengthTable.h"
#include "Tokenizer.h"
#include "QueryResult.h"
#include "SpellingCorrector.h"

class QueryProcessor {
private:
    int K;
public:
    std::string maxLengthToken;
    int correctionThreshold;

    QueryProcessor(int _K, int  correctionThreshold, Tokenizer *pTokenizer);

    void indexProduct(Product product);

    std::vector<QueryResult> process(const std::string &query);

//private:
    std::unordered_map<int, Product> productTable;
    InvertedIndex invertedIndex;
    ProductLengthTable productLengthTable;
    Tokenizer *tokenizer{};
    SpellingCorrector spellingCorrector;
};

#endif //TECHNICAL_TEST_LINX_QUERYPROCESSOR_H
