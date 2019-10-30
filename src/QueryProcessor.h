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

class QueryProcessor {
public:
    explicit QueryProcessor(Tokenizer *pTokenizer);
    void indexProduct(Product product);
private:
    std::unordered_map<int, Product> productTable;
    InvertedIndex invertedIndex;
    ProductLengthTable productLengthTable;
    Tokenizer *tokenizer;
};

#endif //TECHNICAL_TEST_LINX_QUERYPROCESSOR_H
