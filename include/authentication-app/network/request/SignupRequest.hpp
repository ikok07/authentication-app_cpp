//
// Created by kok on 10.08.24.
//

#ifndef SIGNUPREQUEST_HPP
#define SIGNUPREQUEST_HPP

#include <string>

#include "../../JSONParseable.h"
using std::string;

class SignupRequest final : public JSONParseable {
public:
    SignupRequest(const string& username, const string& email, const string& password, const string& confirmPassword)
        : username{username}, email{email}, password{password}, confirmPassword{confirmPassword} {}
private:
    string username;
    string email;
    string password;
    string confirmPassword;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SignupRequest, username, email, password, confirmPassword);
};

#endif //SIGNUPREQUEST_HPP
