//
// Created by kok on 12.08.24.
//

#ifndef CRYPTOR_HPP
#define CRYPTOR_HPP

#include <string>
#include <botan/auto_rng.h>

using std::string;

class Cryptor {
public:
    Cryptor() : key(32) {}
    explicit Cryptor(const string& text) : text{text} {}
    Cryptor(const Cryptor& src) = delete;

    string encrypt_text();
    void save_to_file(const string& filename);
    string& decrypt_from_file(const string& filename);
private:
    string text;
    Botan::secure_vector<uint8_t> key;
    Botan::secure_vector<uint8_t> iv;
    Botan::secure_vector<uint8_t> data;
};



#endif //CRYPTOR_HPP
