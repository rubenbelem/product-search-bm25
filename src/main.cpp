#include <iostream>
#include <fstream>
#include <cstring>
#include "QueryProcessor.h"
#include "Tokenizer.h"
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

bool compareQueryResultsByID(const QueryResult &queryResult1,
                             const QueryResult &queryResult2) {
    return queryResult1.product.id < queryResult2.product.id;
}

int main(int argc, char *argv[]) {
    ifstream productsFile;
    ifstream stopWordsFile;

    // If there isn't enough args...
    if (argc < 3) {
        cerr
                << "Usage: ./processor <products-file-path> "
                   "<stopwords-file-path>";
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

    cout << "Welcome to Ruben's Query Processor!\n\nChoose an option below "
            "to sort query results by product ID, or by the score value.\n\n"
            "1) Sort by ID\n2) Sort by Score\n\n";

    string sortOption;

    while (true) {
        cout << "Type the number of desired sorting option here: ";

        getline(cin, sortOption);

        if (sortOption == "1" || sortOption == "2") break;
        else {
            cout << "The option you typed is invalid! Please try again.\n\n";
        }
    }

    cout << "\nAlright! The indexing step is starting right now.\n\n";

    Tokenizer tokenizer(stopWordsFile);
    QueryProcessor queryProcessor(20, &tokenizer);

    // Indexing step
    try {
        string line;

        while (getline(productsFile, line)) {
            Product product;
            product.buildFrom(line);

            queryProcessor.indexProduct(product);
        }
    }
    catch (std::exception &e) {
        cerr << "\nAn error occurred in the indexing step! Query Processor is "
                "now being shutdown.";
        return 2;
    }

    productsFile.close();
    stopWordsFile.close();

    cout << "\bThe indexing step has finished! Starting Query Processor. "
            "\n\nYou can type \"$exit()\" (without quotes) anytime to finish "
            "the program.\n";



    while (true) {
        string query;

        cout << "\n> Type your query here: ";

        std::getline(cin, query);

        if (query == "$exit()") break;

        auto queryResults = queryProcessor.process(query);

        // The queryResults array already comes sorted from queryProcessor
        // So, if the user choose sortOption 2 there's nothing to do with the
        // aqueryResults rray.
        if (sortOption == "1") {
            std::sort(queryResults.begin(), queryResults.end(),
                      compareQueryResultsByID); // sorting by product ID
         }

        cout << endl;
        int i = 1;
        for (auto queryResult : queryResults) {
            cout << "#" << i << " - \"" << queryResult.product.id << "\" - \""
                 << queryResult.product.name << "\"" << endl;
            ++i;
        }


    }


    return 0;
}