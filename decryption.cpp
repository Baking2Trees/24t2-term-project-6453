#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// Function to load RSA private key from a string
RSA* load_private_key(const std::string& private_key_str) {
    RSA* rsa = nullptr;
    BIO* bio = BIO_new_mem_buf(private_key_str.data(), private_key_str.size());
    if (bio == nullptr) {
        std::cerr << "Error creating BIO object\n";
        return nullptr;
    }

    rsa = PEM_read_bio_RSAPrivateKey(bio, &rsa, nullptr, nullptr);
    if (rsa == nullptr) {
        std::cerr << "Error loading private key\n";
    }

    BIO_free(bio);
    return rsa;
}

// Function to load encrypted data from a file
std::vector<unsigned char> load_encrypted_data(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return {};
    }

    std::vector<unsigned char> data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    return data;
}

// Function to verify the signature using the sender's public key
bool verify_signature(const std::vector<unsigned char>& data, 
                      const std::vector<unsigned char>& signature, 
                      RSA* sender_public_key) {
    EVP_PKEY* evp_key = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(evp_key, sender_public_key);

    EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();
    EVP_PKEY_CTX* pkey_ctx;

    if (EVP_DigestVerifyInit(md_ctx, &pkey_ctx, EVP_sha256(), NULL, evp_key) <= 0) {
        EVP_MD_CTX_free(md_ctx);
        return false;
    }

    if (EVP_DigestVerifyUpdate(md_ctx, data.data(), data.size()) <= 0) {
        EVP_MD_CTX_free(md_ctx);
        return false;
    }

    int result = EVP_DigestVerifyFinal(md_ctx, signature.data(), signature.size());

    EVP_MD_CTX_free(md_ctx);
    EVP_PKEY_free(evp_key);

    return result == 1; // 1 if verification is successful
}

// Function to decrypt the encrypted data using the receiver's private key
std::vector<unsigned char> decrypt_data(const std::vector<unsigned char>& encrypted_data, RSA* receiver_private_key) {
    int rsa_size = RSA_size(receiver_private_key);
    std::vector<unsigned char> decrypted_data(rsa_size);

    int decrypted_len = RSA_private_decrypt(encrypted_data.size(), encrypted_data.data(), decrypted_data.data(), receiver_private_key, RSA_PKCS1_OAEP_PADDING);
    if (decrypted_len == -1) {
        unsigned long err = ERR_get_error(); // Get the error code
        char err_msg[120];
        ERR_error_string_n(err, err_msg, sizeof(err_msg));
        std::cerr << "Error decrypting message: " << err_msg << std::endl;
        return std::vector<unsigned char>();
    }

    decrypted_data.resize(decrypted_len); // Resize to actual data length
    return decrypted_data;
}

// Function to receive and decrypt data
bool ReceiveAndDecrypt(const std::string& encryptedDataFilename, 
                       const std::vector<unsigned char>& senderSignature, 
                       const std::string& senderPublicKeyStr, 
                       const std::string& receiverPrivateKeyStr, 
                       std::vector<unsigned char>& decryptedData) {
    // Load the sender's public key
    RSA* sender_public_key = load_public_key(senderPublicKeyStr);
    if (!sender_public_key) {
        std::cerr << "Failed to load sender's public key\n";
        return false;
    }

    // Load the encrypted data from the file
    std::vector<unsigned char> encryptedData = load_encrypted_data(encryptedDataFilename);
    if (encryptedData.empty()) {
        std::cerr << "Failed to load encrypted data\n";
        RSA_free(sender_public_key);
        return false;
    }

    // Verify the sender's signature
    if (!verify_signature(encryptedData, senderSignature, sender_public_key)) {
        std::cerr << "Invalid signature. The data may have been tampered with.\n";
        RSA_free(sender_public_key);
        return false;
    }

    // Load the receiver's private key
    RSA* receiver_private_key = load_private_key(receiverPrivateKeyStr);
    if (!receiver_private_key) {
        std::cerr << "Failed to load receiver's private key\n";
        RSA_free(sender_public_key);
        return false;
    }

    // Decrypt the data
    decryptedData = decrypt_data(encryptedData, receiver_private_key);
    if (decryptedData.empty()) {
        std::cerr << "Decryption failed.\n";
        RSA_free(sender_public_key);
        RSA_free(receiver_private_key);
        return false;
    }

    // Clean up
    RSA_free(sender_public_key);
    RSA_free(receiver_private_key);

    return true;
}
