#include <iostream>
#include <fstream>
#include <cstring>
#include "QueryProcessor.h"
#include "Tokenizer.h"
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

bool compareQueryResultsForCLI(const QueryResult &queryResult1,
                               const QueryResult &queryResult2) {
    return queryResult1.product.id < queryResult2.product.id;
}

int main(int argc, char *argv[]) {
    ifstream productsFile;
    ifstream stopWordsFile;

    // If there isn't enough args...
    if (argc < 3) {
        cerr
                << "Usage: ./processador <products-file-path> <stopwords-file-path>";
        return 1;
    }

    productsFile.open(argv[1]);

    // If it fails to open Products File
    if (productsFile.fail()) {
        cerr << "The products file on path \"" << argv[1]
             << "\" was not found.";
        return 1;
    }

    stopWordsFile.open(argv[2]);

    // If it fails to open Stop Words File
    if (stopWordsFile.fail()) {
        cerr << "The stop words file on path \"" << argv[2]
             << "\" was not found.";
        return 1;
    }

    Tokenizer tokenizer(stopWordsFile);
    QueryProcessor queryProcessor(20, &tokenizer);

    string line;

    while (getline(productsFile, line)) {
        Product product;
        product.buildFrom(line);

        queryProcessor.indexProduct(product);
    }

    productsFile.close();
    stopWordsFile.close();

    while (true) {
        string query;
        cout << "> Digite aqui sua consulta: ";

        cin.clear();

        cin >> query;


        auto queryResults = queryProcessor.process(query);

        std::sort(queryResults.begin(), queryResults.end(),
                  compareQueryResultsForCLI); // sorting by product ID

        int i = 1;
        for (auto queryResult : queryResults) {
            cout << "#" << i << " - \"" << queryResult.product.id << "\" - \""
                 << queryResult.product.name << "\"" << endl;
            ++i;
        }
    }


    return 0;
}