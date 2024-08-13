//
// Created by kok on 06.08.24.
//

#include "../include/authentication-app/Application.h"

#include <iostream>

#include "../include/authentication-app/Auth.h"
#include "../include/authentication-app/DetailsManager.hpp"

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

void Application::display_main() {
    try {
        int option = -1;
        cout << "------------ ACCOUNT OPTIONS ------------" << endl;

        cout << "Select option: " << endl;
        cout << "1. Create details" << endl;
        // cout << "2. Sign Up" << endl;
        cout << "-1. Log Out" << endl;
        cout << "-2. Exit" << endl;

        cin >> option;

        switch(option) {
            case -1:
                break;
            case 1:
                DetailsManager::create_details();
                break;
            case -2: exit(0);
            default:
                cerr << "Invalid option selected!" << endl;
        }

    } catch (const exception& ex) {
        cout << ex.what() << endl;
    }
}
