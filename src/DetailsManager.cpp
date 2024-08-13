//
// Created by kok on 13.08.24.
//

#include "../include/authentication-app/DetailsManager.hpp"

#include <iostream>
#include <fstream>

#include "../include/authentication-app/Auth.h"
#include "../include/authentication-app/Request.h"
#include "../include/authentication-app/network/request/CreateDetailsRequest.hpp"

using std::cout, std::endl, std::cin;

UserDetails *DetailsManager::details = nullptr;

bool DetailsManager::has_details() {
    return false;
}

void DetailsManager::create_details() {
    string gender;
    short age;
    cout << "Enter your gender: ";
    cin >> gender;
    cout << "Enter your age: ";
    cin >> age;
    const std::unique_ptr<string> token = Auth::get_credentials();
    if (token == nullptr) throw std::runtime_error("Failed to get credentials!");
    rheader_t auth_header = {"Authorization", "Bearer " + *token};
    roptions_t opts = {.headers = {auth_header}};
    Request req{"http://localhost:8080/api/v1/user/details/", &opts};
    CreateDetailsRequest body{gender, age};
    auto res = req.post<CreateDetailsResponse, CreateDetailsRequest>(body);
    std::ofstream file{"details.bin", std::ios::out};
    file << res.get_details();
    cout << "Details successfully created!" << endl;
}
