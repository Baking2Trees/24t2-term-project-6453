#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <string>
#include <vector>

// Load RSA public key from a PEM-formatted string
RSA* load_public_key(const std::string& public_key_str);

// Load RSA private key from a PEM-formatted string
RSA* load_private_key(const std::string& private_key_str);

// Load encrypted data from a file
std::vector<unsigned char> load_encrypted_data(const std::string& filename);

// Load the signature from a file
std::vector<unsigned char> load_signature(const std::string& filename);

// Verify the signature using the sender's public key
bool verify_signature(const std::vector<unsigned char>& data, 
                      const std::vector<unsigned char>& signature, 
                      RSA* sender_public_key);

// Decrypt the encrypted data using the receiver's private key
std::vector<unsigned char> decrypt_data(const std::vector<unsigned char>& encrypted_data, RSA* receiver_private_key);

// Receive and decrypt data
bool ReceiveAndDecrypt(const std::string& encryptedDataFilename, 
                       const std::string& signatureFilename, 
                       const std::string& senderPublicKeyStr, 
                       const std::string& receiverPrivateKeyStr, 
                       std::vector<unsigned char>& decryptedData);

#endif // DECRYPTION_H
