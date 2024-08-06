#ifndef UPLOAD_H
#define UPLOAD_H

#include <string>
#include <vector>
#include <openssl/rsa.h>

class FileUploader {
private:
    std::string uploadDirectory;
    RSA* privateKey;
    RSA* publicKey;

    std::vector<unsigned char> encryptData(const std::vector<unsigned char>& data);
    std::vector<unsigned char> signData(const std::vector<unsigned char>& data);
    std::string getFileName(const std::string& filePath);

public:
    FileUploader(const std::string& directory, const std::string& privateKeyPath, const std::string& publicKeyPath);
    ~FileUploader();

    bool uploadFile(const std::string& filePath);

    // New methods
    static RSA* loadPrivateKey(const std::string& keyPath);
    static RSA* loadPublicKey(const std::string& keyPath);
};

#endif // UPLOAD_H