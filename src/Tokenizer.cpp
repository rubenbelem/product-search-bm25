//
// Created by rubelem on 10/29/19.
//

#include "Tokenizer.h"
#include <cstring>
#include <sstream>
#include <iostream>
#include <string>


using namespace std;

std::vector<std::string> Tokenizer::get(const std::string &s) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while (std::getline(tokenStream, token, ' ')) {
        if (token != "") // if token is not empty, add to the return list.
            tokens.push_back(token);
    }

    return tokens;
}

