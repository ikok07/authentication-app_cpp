//
// Created by kok on 06.08.24.
//

#include "../include/authentication-app/Auth.h"

#include "../include/authentication-app/Request.h"
#include "../include/authentication-app/User.h"
#include "../include/authentication-app/network/request/SignupRequest.hpp"
#include "../include/authentication-app/network/response/SignupResponse.hpp"

#include <fstream>

using namespace std;

User *Auth::user = nullptr;

bool Auth::is_authenticated() {
    return user != nullptr;
}

void Auth::login() {
    Auth::user = new User{};
}

void Auth::signup() {
    string username, email, password, confirmPassword;
    cout << "Enter account username: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, username);
    cout << "Enter account email: ";
    cin >> email;
    cout << "Enter account password: ";
    cin >> password;
    cout << "Confirm account password: ";
    cin >> confirmPassword;

    SignupRequest body{username, email, password, confirmPassword};
    Request req{"http://localhost:8080/api/v1/user/signup"};
    auto res = req.post<SignupResponse, SignupRequest>(body);

    save_credentials(res.get_token());

    auto *res_user = new User;
    *res_user = res.get_user();
    user = res_user;
}

void Auth::save_credentials(const string& token) {
    ofstream file{"auth.bin", ios::out | ios::binary};
    if (!file) throw ios_base::failure("Failed to open file for writing!");
    file.write(token.c_str(), static_cast<long int>(token.length() + 1));
    file.close();
}
