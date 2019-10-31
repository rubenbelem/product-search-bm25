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

// Index a product in the query processor
void QueryProcessor::indexProduct(Product product) {
    /* Tokenizing the product name, to map UTF-8 characters to ISO 8859-1,
     * remove punctuation and linebreaks,
     * turn all the text to lower case and split the name into a vector of words (tokens) */
    auto tokens = tokenizer->extractFrom(product.name);

    // Setting an index id to the product being indexed
    product.indexId = this->productTable.size() + 1;

    this->productTable[product.indexId] = product;

    // For every word tokenized, add it to spelling corrector and to the inverted index
    for (string token : tokens) {
        this->spellingCorrector.addWord(token);
        this->invertedIndex.add(token, product.indexId);
    }

    // Update Product Lenght Table, to be used in process() method
    this->productLengthTable.add(product.indexId, tokens.size());
}

bool compareQueryResults(const QueryResult &queryResult1,
                         const QueryResult &queryResult2) {
    return queryResult1.score < queryResult2.score;
}

// Process query to fetch canditate products that were indexed
vector<QueryResult> QueryProcessor::process(const string &query) {
    unordered_map<int, double> queryResults;
    vector<QueryResult> results;

    // Tokenizing query
    auto queryTokens = tokenizer->extractFrom(query);

    if (queryTokens.empty()) return results;

    // score Products with BM25 for each token and combining by summing scores
    for (string queryToken : queryTokens) {
        // try to correct if the index doesn't have the term
        if (!this->invertedIndex.hasWord(queryToken)) {
            if (queryToken.size() > this->correctionThreshold) continue;
            queryToken = this->spellingCorrector.correct(queryToken);
        }

        if (queryToken.empty()) continue;

        unordered_map<int, int> *invertedList = this->invertedIndex.getInvertedList(
                queryToken);

        // If there is a inverted list for this token
        if (invertedList != nullptr) {
            for (auto item : *invertedList) {
                int productIndexId = item.first;
                int frequency = item.second;

                // BM25 score for this product, considering the current queryToken
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

    vector<QueryResult> resultHeap;

    // Iterate over query results to order them by score, by inserting them into a Heap
    for (auto queryResult : queryResults) {
        Product p = this->productTable[queryResult.first];
        double score = queryResult.second;

        resultHeap.emplace_back(p, score);

        std::push_heap(resultHeap.begin(), resultHeap.end(),
                       compareQueryResults);
    }

    // pop only the Top-K results from the resultHeap
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
