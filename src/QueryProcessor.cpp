//
// Created by rubelem on 10/30/19.
//

#include <string>
#include "QueryProcessor.h"

using namespace std;

void QueryProcessor::indexProduct(Product product) {
    auto tokens = tokenizer->extractFrom(product.name);
}

QueryProcessor::QueryProcessor(Tokenizer *pTokenizer) : tokenizer(pTokenizer) {

}

