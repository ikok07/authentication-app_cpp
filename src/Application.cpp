//
// Created by kok on 06.08.24.
//

#include "../include/authentication-app/Application.h"

#include <iostream>

#include "../include/authentication-app/Auth.h"

using namespace std;

void Application::display_auth() {
    try {
        int option = -1;
        cout << "------------ AUTHENTICATION OPTIONS ------------" << endl;

        cout << "Select option: " << endl;
        cout << "1. Log In" << endl;
        cout << "2. Sign Up" << endl;
        cout << "-1. Exit" << endl;

        cin >> option;
        if (option == -1) exit(0);

        switch (option) {
            case 1:
                Auth::login();
                break;
            case 2:
                Auth::signup();
                break;
            default:
                cerr << "Invalid option selected!" << endl;
        }
    } catch(const exception& ex) {
        cout << ex.what() << endl;
    }
}
