//
// Created by rubelem on 10/30/19.
//

#include <string>
#include "QueryProcessor.h"

using namespace std;

void QueryProcessor::indexProduct(Product product) {
    auto tokens = tokenizer->extractFrom(product.name);
    int indexId = this->productTable.size();
    product.indexId = indexId;

    this->productTable[indexId] = product;
}

QueryProcessor::QueryProcessor(Tokenizer *pTokenizer) : tokenizer(pTokenizer) {

}

