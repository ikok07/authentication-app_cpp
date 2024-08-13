#include <iostream>
#include <curlpp/cURLpp.hpp>

#include "../include/authentication-app/Application.h"
#include "../include/authentication-app/Auth.h"
#include "../include/authentication-app/Request.h"

#include <botan/hash.h>
#include <botan/hex.h>
#include <botan/cipher_mode.h>
#include <botan/aead.h>
#include <botan/auto_rng.h>
#include <botan/rng.h>

#include "../include/authentication-app/Cryptor.hpp"

using namespace std;

int main() {
    cURLpp::initialize(CURL_GLOBAL_SSL);

    while (!Auth::is_authenticated()) Application::display_auth();

    cout << "Account info: " << endl;
    cout << Auth::user->username << '\n';
    cout << Auth::user->email << endl;

    Application::display_main();

    return 0;
}
