#include <iostream>
#include <fstream>
#include <cstring>
#include "../deps/json/json.hpp"
#include "Product.h"
#include "Tokenizer.h"
#include <unordered_map>
using namespace std;
using nlohmann::json;

int main( int argc, char *argv[] ) {
    ifstream productsFile;
    ifstream stopwordsFile;

    if (argc < 3) {
        cerr << "Usage: ./processador <products-file-path> <stopwords-file-path>";
        return 1;
    }

    productsFile.open(argv[1]);

    if (productsFile.fail()) {
        cerr << "The products file on path \"" << argv[1] << "\" was not found.";
        return 1;
    }

    stopwordsFile.open(argv[2]);

    if (stopwordsFile.fail()) {
        cerr << "The stop words file on path \"" << argv[2] << "\" was not found.";
        return 1;
    }

    Tokenizer tokenizer(stopwordsFile);

    string line;

    while(getline(productsFile, line)) {
        Product product;
        auto productJson = json::parse(line);
        productJson.at("id").get_to(product.id);
        productJson.at("name").get_to(product.name);

        auto tokens = tokenizer.extractFrom(product.name);

        for (const string& token : tokens) {
            cout << token << "|";
        }
        cout << endl;
    }

    ofstream charCounting("../test/char_counting.txt");

    productsFile.close();
    return 0;
}