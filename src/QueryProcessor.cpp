//
// Created by rubelem on 10/30/19.
//

#include <string>
#include "QueryProcessor.h"

using namespace std;

void QueryProcessor::indexProduct(Product product) {
    auto tokens = tokenizer->extractFrom(product.name);
    product.indexId = this->productTable.size() + 1;

    this->productTable[product.indexId] = product;

    for (string token : tokens) {
        this->invertedIndex.add(token, product.indexId);
    }
}

QueryProcessor::QueryProcessor(Tokenizer *pTokenizer) : tokenizer(pTokenizer) {

}

