//
// Created by kok on 12.08.24.
//

#ifndef FILENOTFOUND_HPP
#define FILENOTFOUND_HPP

#include <string>
#include <exception>

class FileNotFound: public std::exception {
public:
    explicit FileNotFound(const char *msg) : msg{msg} {}
    const char* what() const noexcept override {return msg.c_str();};
private:
    std::string msg;
};

#endif //FILENOTFOUND_HPP
