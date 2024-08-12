//
// Created by kok on 12.08.24.
//

#ifndef LOGINRESPONSE_HPP
#define LOGINRESPONSE_HPP
#include "../../JSONParseable.h"
#include "../../User.h"

using std::string;

class LoginResponse final : public JSONParseable {
public:
    const string& get_token() {return token;}
    const User& get_user() {return user;}
private:
    string status;
    string token;
    User user;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginResponse, status, token, user);
};


#endif //LOGINRESPONSE_HPP
