//
// Created by kok on 12.08.24.
//

#ifndef GETUSERRESPONSE_HPP
#define GETUSERRESPONSE_HPP
#include "../../JSONParseable.h"
#include "../../User.h"

class GetUserResponse final : public JSONParseable {
public:
    const User& get_user() {return user;}
private:
    std::string status;
    User user;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetUserResponse, status, user);
};

#endif //GETUSERRESPONSE_HPP
