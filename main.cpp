#include <iostream>

#include "sha256.h"

int main (void) {
    const unsigned char data[] = "hello world";
    std::cout << "Hash function is working correctly if " << data << " hashes to: b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9\n";
    std::cout << "Here is the computed hash for our implementation\n";
    std::cout << "input: " << data << "\n";
    std::cout << "hash: " << SHA256_hash_as_string(data, sizeof(data) - 1) << "\n";
    return 0;
}