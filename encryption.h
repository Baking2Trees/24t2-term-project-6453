#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <vector>

// Load RSA public key from a PEM-formatted string
RSA* load_public_key(const std::string& public_key_str);

// Encrypt data using RSA public key
std::string encrypt_data(RSA* rsa, const std::string& data);

// Load RSA private key from a PEM-formatted string
RSA* load_private_key(const std::string& private_key_str);

// Sign data using RSA private key
std::vector<unsigned char> sign_data(RSA* rsa, const std::string& data);

// Encrypt and send data
void EncryptAndSend(const std::string& requestedData, 
                    const std::string& requesterPublicKey, 
                    const std::string& senderPrivateKey, 
                    const std::string& encryptedDataFilename, 
                    const std::string& signatureFilename);

#endif // ENCRYPTION_H
