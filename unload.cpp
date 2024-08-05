#include "upload.h"
#include <iostream>
#include <fstream>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>

FileUploader::FileUploader(const std::string& directory, const std::string& privateKeyPath, const std::string& publicKeyPath)
    : uploadDirectory(directory) {
    privateKey = loadPrivateKey(privateKeyPath);
    publicKey = loadPublicKey(publicKeyPath);
    if (!privateKey || !publicKey) {
        throw std::runtime_error("Failed to load keys");
    }
}

FileUploader::~FileUploader() {
    if (privateKey) RSA_free(privateKey);
    if (publicKey) RSA_free(publicKey);
}

bool FileUploader::uploadFile(const std::string& filePath) {
    try {
        // Read file content
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file: " + filePath);
        }
        std::vector<unsigned char> fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // Encrypt data
        std::vector<unsigned char> encryptedData = encryptData(fileContent);

        // Sign data
        std::vector<unsigned char> signature = signData(encryptedData);

        // Write encrypted data to file
        std::string uploadedFilePath = uploadDirectory + "/" + getFileName(filePath) + ".encrypted";
        std::ofstream outFile(uploadedFilePath, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Failed to create output file: " + uploadedFilePath);
        }
        outFile.write(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());

        // Write signature to separate file
        std::string signatureFilePath = uploadedFilePath + ".sig";
        std::ofstream sigFile(signatureFilePath, std::ios::binary);
        if (!sigFile) {
            throw std::runtime_error("Failed to create signature file: " + signatureFilePath);
        }
        sigFile.write(reinterpret_cast<const char*>(signature.data()), signature.size());

        std::cout << "File encrypted and uploaded successfully: " << uploadedFilePath << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error uploading file: " << e.what() << std::endl;
        return false;
    }
}

std::vector<unsigned char> FileUploader::encryptData(const std::vector<unsigned char>& data) {
    std::vector<unsigned char> encryptedData(RSA_size(publicKey));
    int encryptedLength = RSA_public_encrypt(data.size(), data.data(), encryptedData.data(), publicKey, RSA_PKCS1_OAEP_PADDING);
    if (encryptedLength == -1) {
        throw std::runtime_error("Encryption failed");
    }
    encryptedData.resize(encryptedLength);
    return encryptedData;
}

std::vector<unsigned char> FileUploader::signData(const std::vector<unsigned char>& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(data.data(), data.size(), hash);

    std::vector<unsigned char> signature(RSA_size(privateKey));
    unsigned int signatureLength;
    if (RSA_sign(NID_sha256, hash, SHA256_DIGEST_LENGTH, signature.data(), &signatureLength, privateKey) != 1) {
        throw std::runtime_error("Signing failed");
    }
    signature.resize(signatureLength);
    return signature;
}

RSA* FileUploader::loadPrivateKey(const std::string& keyPath) {
    FILE* file = fopen(keyPath.c_str(), "r");
    if (!file) {
        throw std::runtime_error("Failed to open private key file");
    }
    RSA* rsa = PEM_read_RSAPrivateKey(file, NULL, NULL, NULL);
    fclose(file);
    if (!rsa) {
        throw std::runtime_error("Failed to load private key");
    }
    return rsa;
}

RSA* FileUploader::loadPublicKey(const std::string& keyPath) {
    FILE* file = fopen(keyPath.c_str(), "r");
    if (!file) {
        throw std::runtime_error("Failed to open public key file");
    }
    RSA* rsa = PEM_read_RSA_PUBKEY(file, NULL, NULL, NULL);
    fclose(file);
    if (!rsa) {
        throw std::runtime_error("Failed to load public key");
    }
    return rsa;
}

std::string FileUploader::getFileName(const std::string& filePath) {
    size_t pos = filePath.find_last_of("/\\");
    return (pos == std::string::npos) ? filePath : filePath.substr(pos + 1);
}