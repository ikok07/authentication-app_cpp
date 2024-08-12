//
// Created by kok on 12.08.24.
//

#include "Cryptor.hpp"

#include <iostream>

#include <botan/aead.h>
#include <botan/hex.h>
#include <fstream>

#include "../include/authentication-app/exceptions/FileNotFound.hpp"

string Cryptor::encrypt_text() {
    if (text.empty()) throw std::runtime_error("There isn't any text set in order to be encrypted!");
    Botan::AutoSeeded_RNG rng;
    this->key = rng.random_vec(32);

    const auto enc = Botan::AEAD_Mode::create_or_throw("AES-256/GCM", Botan::Cipher_Dir::Encryption);
    this->iv = rng.random_vec(enc->default_nonce_length());
    this->data = Botan::secure_vector<uint8_t>(this->text.begin(), this->text.begin() + this->text.size());

    enc->set_key(this->key);
    enc->start(iv);
    enc->finish(data);
    return hex_encode(data);
}

void Cryptor::save_to_file(const string &filename) {
    if (this->text.empty()) throw std::runtime_error("Cryptor object is missing encrypted text in order to save it to a file!");
    std::ofstream file{filename, std::ios::out | std::ios::binary};
    if (file.fail()) throw std::runtime_error("Failed to open file for writing!");
    size_t data_size = this->data.size();
    file.write(reinterpret_cast<char*>(this->key.data()), this->key.size());
    file.write(reinterpret_cast<char*>(this->iv.data()), this->iv.size());
    file.write(reinterpret_cast<char*>(&data_size), sizeof(size_t));
    file.write(reinterpret_cast<char*>(this->data.data()), this->data.size());

    file.close();
}

string& Cryptor::decrypt_from_file(const string &filename) {
    std::ifstream file{filename, std::ios::in | std::ios::binary};
    if (file.fail()) throw FileNotFound("Failed to open file for reading!");
    const auto dec = Botan::AEAD_Mode::create_or_throw("AES-256/GCM", Botan::Cipher_Dir::Decryption);

    file.read(reinterpret_cast<char*>(this->key.data()), 32);
    if (this->key.empty()) {};
    this->iv.resize(dec->default_nonce_length());
    file.read(reinterpret_cast<char*>(this->iv.data()), dec->default_nonce_length());

    size_t data_size;
    file.read(reinterpret_cast<char*>(&data_size), sizeof(size_t));

    this->data.resize(data_size);
    file.read(reinterpret_cast<char*>(this->data.data()), data_size);

    dec->set_key(this->key);
    dec->start(iv);
    dec->finish(data);

    this->text = string(this->data.begin(), this->data.end());
    return this->text;
}
