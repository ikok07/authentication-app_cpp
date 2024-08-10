//
// Created by kok on 06.08.24.
//

#ifndef USER_H
#define USER_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/detail/macro_scope.hpp>

using std::string;

struct User {
    string _id;
    string username;
    string email;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(User, _id, username, email);
};

#endif //USER_H
