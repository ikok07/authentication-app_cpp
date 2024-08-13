//
// Created by kok on 13.08.24.
//

#ifndef CREATEDETAILS_HPP
#define CREATEDETAILS_HPP
#include "../../JSONParseable.h"

#include <string>
#include <nlohmann/json.hpp>

#include "../response/CreateDetailsResponse.hpp"

class CreateDetailsRequest : public JSONParseable {
public:
    CreateDetailsRequest(const string& gender, short age) : gender{gender}, age{age} {}
private:
    std::string gender;
    short age;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CreateDetailsRequest, gender, age);
};

#endif //CREATEDETAILS_HPP
