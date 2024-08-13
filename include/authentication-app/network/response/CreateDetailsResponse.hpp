//
// Created by kok on 13.08.24.
//

#ifndef CREATEDETAILSRESPONSE_HPP
#define CREATEDETAILSRESPONSE_HPP
#include "../../JSONParseable.h"
#include "../../UserDetails.hpp"

#include <string>

class CreateDetailsResponse : JSONParseable {
public:
    const UserDetails& get_details() {return data;};
private:
    std::string status;
    UserDetails data;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CreateDetailsResponse, status, data);
};

#endif //CREATEDETAILSRESPONSE_HPP
