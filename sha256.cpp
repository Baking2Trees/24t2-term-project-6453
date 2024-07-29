#include <openssl/evp.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "sha256.h"

#define HASH_SIZE 32

void compute_SHA256(const unsigned char* data, size_t dataLen, unsigned char* hash) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, EVP_sha256(), nullptr); // Initalise context
    EVP_DigestUpdate(context, data, dataLen); // Hash input data
    unsigned int length_of_hash;
    EVP_DigestFinal_ex(context, hash, &length_of_hash); // Finialse the hash
    EVP_MD_CTX_free(context);
}

// Computes a SHA256 hash and then returns it as a std::string
std::string SHA256_hash_as_string(const unsigned char* data, size_t dataLen) {
    unsigned char hash[HASH_SIZE];
    compute_SHA256(data, dataLen, hash);
    
    // Converts the byte data to a string
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < HASH_SIZE; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    return ss.str();
}