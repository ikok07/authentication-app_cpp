//
// Created by kok on 06.08.24.
//

#ifndef AUTH_H
#define AUTH_H
#include "User.h"

class Auth {
public:
    static User *user;
    static bool is_authenticated();
    static void login();
    static void signup();
private:
    static void save_credentials(const string& token);
};



#endif //AUTH_H
