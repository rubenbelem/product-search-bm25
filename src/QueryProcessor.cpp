//
// Created by rubelem on 10/30/19.
//

#include <string>
#include "QueryProcessor.h"
#include "Scoring.h"

using namespace std;
using namespace scoring;

void QueryProcessor::indexProduct(Product product) {
    auto tokens = tokenizer->extractFrom(product.name);
    product.indexId = this->productTable.size() + 1;

    this->productTable[product.indexId] = product;

    for (string token : tokens) {
        this->invertedIndex.add(token, product.indexId);
    }

    this->productLengthTable.add(product.indexId, tokens.size());
}

vector<QueryResult> QueryProcessor::process(const string& query) {
    unordered_map<int, double> queryResults;
    vector<QueryResult> products;
    auto queryTokens = tokenizer->extractFrom(query);

    if (queryTokens.empty()) return products;

    for (auto queryToken : queryTokens) {
        if (this->invertedIndex.hasWord(queryToken)) {
            unordered_map<int, int> *invertedList = this->invertedIndex.getInvertedList(queryToken);

            if (invertedList != nullptr) {
                for (auto item : *invertedList) {
                    int productIndexId = item.first;
                    int frequency = item.second;

                    double score = scoring::BM25::score(invertedList->size(), frequency, 1, 0, this->productLengthTable.getTableSize(), this->productLengthTable.getLength(productIndexId), this->productLengthTable.getAverageSize());

                    queryResults[productIndexId] += score;
                }
            }
        }
    }

    int i = 0;
    for (auto queryResult : queryResults) {
        Product p = this->productTable[queryResult.first];
        double score = queryResult.second;

        products.emplace_back(p, score);
        ++i;

        if (i == 20) break;
    }

    return products;
}

QueryProcessor::QueryProcessor(Tokenizer *pTokenizer) : tokenizer(pTokenizer) {}
