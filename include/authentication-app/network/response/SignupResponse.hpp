//
// Created by kok on 10.08.24.
//

#ifndef SIGNUPRESPONSE_HPP
#define SIGNUPRESPONSE_HPP
#include "../../JSONParseable.h"

#include <string>

using std::string;

class SignupResponse : public JSONParseable {
public:
    const string& get_token() const {return token;}
    const User& get_user() const {return user;}
private:
    string status;
    string token;
    User user;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SignupResponse, status, token, user);
};

#endif //SIGNUPRESPONSE_HPP
