#ifndef RECEIVE_AND_DECRYPT_H
#define RECEIVE_AND_DECRYPT_H

#include <string>
#include <vector>
#include <openssl/rsa.h>

// Function to load RSA private key from a PEM-formatted string
RSA* load_private_key(const std::string& private_key_str);

// Function to load encrypted data from a file
std::vector<unsigned char> load_encrypted_data(const std::string& filename);

// Function to verify the signature using the sender's public key
bool verify_signature(const std::vector<unsigned char>& data, 
                      const std::vector<unsigned char>& signature, 
                      RSA* sender_public_key);

// Function to decrypt data using an RSA private key
std::vector<unsigned char> rsa_decrypt(const std::vector<unsigned char>& encrypted_bytes, RSA* private_key);

// Function to receive and decrypt data
bool ReceiveAndDecrypt(const std::string& encryptedDataFilename, 
                       const std::vector<unsigned char>& senderSignature, 
                       const std::string& senderPublicKeyStr, 
                       const std::string& receiverPrivateKeyStr, 
                       std::vector<unsigned char>& decryptedData);

#endif // RECEIVE_AND_DECRYPT_H
