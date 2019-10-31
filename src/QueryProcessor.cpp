//
// Created by rubelem on 10/30/19.
//

#include <string>
#include <algorithm>
#include "QueryProcessor.hpp"
#include "Scoring.hpp"
#include <iostream>

using namespace std;
using namespace scoring;

void QueryProcessor::indexProduct(Product product) {
    auto tokens = tokenizer->extractFrom(product.name);
    product.indexId = this->productTable.size() + 1;

    this->productTable[product.indexId] = product;

    for (string token : tokens) {
        this->spellingCorrector.addWord(token);
        this->invertedIndex.add(token, product.indexId);
    }

    this->productLengthTable.add(product.indexId, tokens.size());
}

bool compareQueryResults(const QueryResult &queryResult1,
                         const QueryResult &queryResult2) {
    return queryResult1.score < queryResult2.score;
}

vector<QueryResult> QueryProcessor::process(const string &query) {
    unordered_map<int, double> queryResults;
    vector<QueryResult> results;

    auto queryTokens = tokenizer->extractFrom(query);

    if (queryTokens.empty()) return results;

    vector<string> suggestedTokens;
    vector<string> finalQueryTokens;

    for (const auto &queryToken : queryTokens) {
        if (!this->invertedIndex.hasWord(queryToken)) {
            if (queryToken.size() > this->correctionThreshold) continue;
            vector<pair<string, int>> suggestions = this->spellingCorrector.getSuggestions(queryToken);

            int i = 0;
            for (const auto &s : suggestions) {
                suggestedTokens.emplace_back(s.first);
                ++i;

                if (i == 5) break;
            }
        } else {
            finalQueryTokens.emplace_back(queryToken);
        }
    }

    finalQueryTokens.insert(finalQueryTokens.end(), suggestedTokens.begin(), suggestedTokens.end());

    for (const auto &queryToken : finalQueryTokens) {
        if (this->invertedIndex.hasWord(queryToken)) {
            unordered_map<int, int> *invertedList = this->invertedIndex.getInvertedList(
                    queryToken);

            if (invertedList != nullptr) {
                for (auto item : *invertedList) {
                    int productIndexId = item.first;
                    int frequency = item.second;

                    double score = scoring::BM25::score(invertedList->size(),
                                                        frequency, 1, 0,
                                                        this->productLengthTable.getTableSize(),
                                                        this->productLengthTable.getLength(
                                                                productIndexId),
                                                        this->productLengthTable.getAverageSize());

                    queryResults[productIndexId] += score;
                }
            }
        }
    }

    vector<QueryResult> resultHeap;

    for (auto queryResult : queryResults) {
        Product p = this->productTable[queryResult.first];
        double score = queryResult.second;

        resultHeap.emplace_back(p, score);

        std::push_heap(resultHeap.begin(), resultHeap.end(),
                       compareQueryResults);
    }

    for (int i = 0; i < resultHeap.size(); ++i) {
        results.push_back(resultHeap.front());

        std::pop_heap(resultHeap.begin(), resultHeap.end(),
                      compareQueryResults);

        resultHeap.pop_back();
        if (i == K - 1) break;
    }

    return results;
}

QueryProcessor::QueryProcessor(int K, int _correctionThreshold, Tokenizer *pTokenizer) : tokenizer(
        pTokenizer), K(K), correctionThreshold(_correctionThreshold) {

}
