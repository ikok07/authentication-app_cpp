//
// Created by kok on 12.08.24.
//

#ifndef LOGINREQUEST_HPP
#define LOGINREQUEST_HPP
#include "../../JSONParseable.h"

#include <string>

using std::string;

class LoginRequest : public JSONParseable {
public:
    LoginRequest(const string& email, const string& password) : email{email}, password{password} {}
private:
    string email;
    string password;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginRequest, email, password);
};

#endif //LOGINREQUEST_HPP
