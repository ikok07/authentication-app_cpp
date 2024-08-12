//
// Created by kok on 06.08.24.
//

#include "../include/authentication-app/Auth.h"

#include "../include/authentication-app/Request.h"
#include "../include/authentication-app/User.h"
#include "../include/authentication-app/network/request/SignupRequest.hpp"
#include "../include/authentication-app/network/response/SignupResponse.hpp"

#include <fstream>

#include "Cryptor.hpp"
#include "../include/authentication-app/network/request/LoginRequest.hpp"
#include "../include/authentication-app/network/response/GetUserResponse.hpp"
#include "../include/authentication-app/network/response/LoginResponse.hpp"
#include "../include/authentication-app/exceptions/FileNotFound.hpp"

using namespace std;

User *Auth::user = nullptr;

bool Auth::is_authenticated() {
    if (user == nullptr) load_credentials();
    else return true;

    return user != nullptr;
}

void Auth::login() {
    string email, password;
    cout << "Enter account email: ";
    cin >> email;
    cout << "Enter account password: ";
    cin >> password;

    LoginRequest body{email, password};
    Request req{"http://localhost:8080/api/v1/user/login"};

    auto res = req.post<LoginResponse, LoginRequest>(body);
    save_credentials(res.get_token());

    auto *new_user = new User();
    *new_user = res.get_user();
    user = new_user;
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
    Cryptor cryptor{token};
    cryptor.encrypt_text();
    cryptor.save_to_file("auth.bin");
}

void Auth::load_credentials() {
    try {
        Cryptor cryptor;
        const string& token = cryptor.decrypt_from_file("auth.bin");
        rheader_t auth_header = {"Authorization", "Bearer " + token};
        roptions_t opts = {.headers = {auth_header}};
        Request req{"http://localhost:8080/api/v1/user/me", &opts};
        auto res = req.get<GetUserResponse>();
        User *new_user = new User();
        *new_user = res.get_user();
        user = new_user;
    }
    catch (const FileNotFound&) {}
    catch (const Botan::Invalid_Argument&) {}
}
