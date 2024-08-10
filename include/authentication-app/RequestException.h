//
// Created by kok on 06.08.24.
//

#ifndef REQUESTERROR_H
#define REQUESTERROR_H
#include <exception>
#include <string>

class RequestException final : public std::exception {
public:
    RequestException() = delete;
    explicit RequestException(std::string msg) : msg{msg} {}
    const char* what() const noexcept override {
        return msg.c_str();
    };
private:
    std::string msg;
};

#endif //REQUESTERROR_H
