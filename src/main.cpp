#include <iostream>
#include <fstream>
#include <cstring>
#include "QueryProcessor.hpp"
#include "Tokenizer.hpp"
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <chrono>
#include "readline/readline.h"
#include "readline/history.h"

using namespace std;

bool compareQueryResultsByID(const QueryResult &queryResult1,
                             const QueryResult &queryResult2) {
    return queryResult1.product.id < queryResult2.product.id;
}

int main(int argc, char *argv[]) {
    ifstream productsFile;
    ifstream stopWordsFile;

    // If there isn't enough args...
    if (argc < 4) {
        cerr << "Usage example: ./processor <product-catalog-file-path> "
                "<stopwords-file-path> <sort-option>\n";
        return 1;
    }

    productsFile.open(argv[1]);

    // If it fails to open Products File
    if (productsFile.fail()) {
        cerr << "The product catalog file at the path \"" << argv[1]
             << "\" wasn't found.\n";
        return 1;
    }

    stopWordsFile.open(argv[2]);

    // If it fails to open Stop Words File
    if (stopWordsFile.fail()) {
        cerr << "The stopwords file at the path \"" << argv[2]
             << "\" wasn't found.\n";
        return 1;
    }

    string sortOption(argv[3]);
    
    // sort option wasn't valid
    if (sortOption != "id" && sortOption != "score") {
        cerr << "The option for sorting the results is not valid. The value must be \"id\" or \"score\"\n";
        return 1;
    }

    cout << "Welcome to Ruben's product query processor!\n";

    cout << "\nAlright, starting the indexing stage.\n";

    Tokenizer tokenizer(stopWordsFile);
    QueryProcessor queryProcessor(20, 15, &tokenizer);

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
        cerr << "\nAn error ocurred during the indexing stage!"
                "The query processor is shutting down.";
        return 1;
    }

    productsFile.close();
    stopWordsFile.close();

    cout << "\nThe indexing stage is finished! Starting the query processor. "
            "\n\nTo navigate through the history of queries you must use the up and down arrow keys."
            "\n\nYou can type \"@exit\" (no quotes) or press Ctrl+C at any moment "
            "to finish the program execution.\n\n";

    const char *line;
    while ((line = readline("> Type your query: ")) != nullptr) {
        if (*line) add_history(line);
        string query(line);

        if (query == "@exit") break;

        // Query processing
        auto start = std::chrono::system_clock::now();
        auto queryResults = queryProcessor.process(query);
        auto end = std::chrono::system_clock::now();

        auto queryProcessingTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (queryResults.empty()) {
            cout << "\nNo result was found.\n";
            
        }
        else {
            // The queryResults array already comes sorted from queryProcessor
            // So, if the user choose sort to by "score" there's nothing left to do with the
            // queryResults array.
            if (sortOption == "id") {
                std::sort(queryResults.begin(), queryResults.end(),
                        compareQueryResultsByID); // sorting by product ID
            }

            cout << endl;
            int i = 1;

            // Printing query results
            for (const auto &queryResult : queryResults) {
                cout << "#" << i << " - \"" << queryResult.product.id << "\" - \""
                    << queryResult.product.name << "\""  << endl;
                ++i;
            }
        }

        cout << "\nQuery processed in " << queryProcessingTime << "ms.\n\n";

        free((void *) line);
    }

    return 0;
}
