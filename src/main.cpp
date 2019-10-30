#include <iostream>
#include <fstream>
#include <cstring>
#include "QueryProcessor.h"
#include "Tokenizer.h"
#include <unordered_map>

using namespace std;

int main( int argc, char *argv[] ) {
    ifstream productsFile;
    ifstream stopWordsFile;

    // If there isn't enough args...
    if (argc < 3) {
        cerr << "Usage: ./processador <products-file-path> <stopwords-file-path>";
        return 1;
    }

    productsFile.open(argv[1]);

    // If it fails to open Products File
    if (productsFile.fail()) {
        cerr << "The products file on path \"" << argv[1] << "\" was not found.";
        return 1;
    }

    stopWordsFile.open(argv[2]);

    // If it fails to open Stop Words File
    if (stopWordsFile.fail()) {
        cerr << "The stop words file on path \"" << argv[2] << "\" was not found.";
        return 1;
    }

    Tokenizer tokenizer(stopWordsFile);
    QueryProcessor queryProcessor(&tokenizer);

    string line;

    while(getline(productsFile, line)) {
        Product product;
        product.buildFrom(line);

        queryProcessor.indexProduct(product);
    }

    ofstream charCounting("../test/char_counting.txt");

    productsFile.close();
    return 0;
}