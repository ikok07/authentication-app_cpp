#include <iostream>
#include <utility>
#include <curlpp/cURLpp.hpp>

#include "../include/authentication-app/Application.h"
#include "../include/authentication-app/Auth.h"
#include "../include/authentication-app/Request.h"

using namespace std;

int main() {
    cURLpp::initialize(CURL_GLOBAL_SSL);

    while (!Auth::is_authenticated()) Application::display_auth();

    cout << Auth::user->username << '\n';
    cout << Auth::user->email << endl;

    return 0;
}
