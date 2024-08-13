//
// Created by kok on 13.08.24.
//

#ifndef DETAILSMANAGER_HPP
#define DETAILSMANAGER_HPP
#include "UserDetails.hpp"


class DetailsManager {
public:
    static UserDetails *details;

    static bool has_details();
    static void create_details();
};



#endif //DETAILSMANAGER_HPP
