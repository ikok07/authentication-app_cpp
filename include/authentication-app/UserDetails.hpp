//
// Created by kok on 13.08.24.
//

#ifndef USERDETAILS_HPP
#define USERDETAILS_HPP

#include <string>
#include <ostream>
#include <nlohmann/json.hpp>

using std::string;

class UserDetails {
    friend inline std::ostream& operator<<(std::ostream& stream, const UserDetails& details);
    string _id;
    string gender;
    short age;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UserDetails, _id, gender, age);
};

std::ostream& operator<<(std::ostream& stream, const UserDetails& details) {
    stream << "ID: " << details._id << '\n';
    stream << "Gender: " << details.gender << '\n';
    stream << "Age: " << details.age << std::endl;
    return stream;
}

#endif //USERDETAILS_HPP
