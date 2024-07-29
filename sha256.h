#ifndef SHA256_H
#define SHA256_H

#include <string>

// Computes a SHA256 hash on a given set of data
// Arguments: data - Pointer to a char array of the data to be hashed
//            dataLen - length of the data in bytes
//            hash    - array where the hash will be stored. Must be length 32 bytes to work as intended
// Returns - nothing but it will populate the empty hash array with the hash
void compute_SHA256(const unsigned char* data, size_t dataLen, unsigned char* hash);

// Computes a SHA256 hash and then returns it as a std::string
std::string SHA256_hash_as_string(const unsigned char* data, size_t dataLen);
// ^^^ Use this one for simplicity

#endif // SHA256_H