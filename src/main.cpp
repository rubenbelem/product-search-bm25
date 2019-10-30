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
    Tokenizer tokenizer;
    unordered_map<string , int> chars;
    if (argc < 2) {
        cout << "The 1st parameter <data_path> must be set!";
        return 1;
    }

    productsFile.open(argv[1]);

    if (productsFile.fail()) {
        cout << "The products file was not found.";
        return 1;
    }

    string line;

    while(getline(productsFile, line)) {
        Product product;
        auto productJson = json::parse(line);
        productJson.at("id").get_to(product.id);
        productJson.at("name").get_to(product.name);

        auto tokens = tokenizer.get(product.name);

        for (const string& token : tokens) {
            cout << token << "|";
        }
        cout << endl;
    }

    ofstream charCounting("../test/char_counting.txt");

    for (auto ch : chars) {
        charCounting << ch.first << " : " << ch.second << endl;
    }

    productsFile.close();
    return 0;
}