#ifndef ENCRYPT_AND_SEND_H
#define ENCRYPT_AND_SEND_H

#include <string>
#include <vector>
#include <openssl/rsa.h>


RSA* load_private_key(const std::string& private_key_str);

std::vector<unsigned char> sign_data(RSA* rsa, const std::string& data);

void EncryptAndSend(const std::string& requestedData, 
                    const std::string& requesterPublicKey, 
                    const std::string& senderPrivateKey, 
                    const std::string& encryptedDataFilename, 
                    const std::string& signatureFilename);

#endif // ENCRYPT_AND_SEND_H
