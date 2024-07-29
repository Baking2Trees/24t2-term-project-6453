#include <openssl/evp.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "sha256.h"
#include "constants.h"

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

std::string merkle_node_sha256_hash(std::string hash1, std::string hash2) {
    // Need to put these hashes next to each other in an array to use the functions we have
    // Get bytes
    std::vector<uint8_t> bytes;

    for (size_t i = 0; i < hash1.length(); i += 2) {
        std::string byteString = hash1.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        bytes.push_back(byte);
    }

    for (size_t i = 0; i < hash2.length(); i += 2) {
        std::string byteString = hash2.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        bytes.push_back(byte);
    }

    // Copy byte data to our array for hash input
    unsigned char data[HASH_SIZE * 2]; // Remember this is two cojoined hashes
    for (int i = 0; i < bytes.size(); i++) {
        data[i] = static_cast<unsigned char>(bytes[i]);
    }

    // Now we have data and can hash
    return SHA256_hash_as_string(data, HASH_SIZE * 2);
}