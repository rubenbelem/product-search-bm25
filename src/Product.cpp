//
// Created by rubelem on 10/30/19.
//

#include <string>
#include "Product.h"
#include "json.hpp"

using namespace std;
using nlohmann::json;

void Product::buildFrom(const std::string& jsonText) {
    auto productJson = json::parse(jsonText);

    productJson.at("id").get_to(this->id);
    productJson.at("name").get_to(this->name);
}

